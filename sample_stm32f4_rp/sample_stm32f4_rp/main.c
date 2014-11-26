
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#include "config_adc.h"
#include "config_encoder.h"
#include "config_port.h"
#include "config_pwm.h"
#include "config_systick.h"
#include "config_usart.h"
#include "config_usb.h"
#include "name_converter.h"
#include "my_standard_io.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

//マクロ定義(関数名をdefine定義する)
#define USB_PC usb_put_char

#define SWITCH GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)			//スイッチ
#define ENCODER_A read_value('a')								//エンコーダa
#define ENCODER_B read_value('b')								//エンコーダb
#define ENCODER_C read_value('c')								//エンコーダc

#define PAI 				3.1415		//円周率
#define PULSE 				400			//エンコーダ一周カウント数
#define ENCODER_DISTANCE 	87.5		//中心からエンコーダまでの距離

//エンコーダ直径(キャリブレーションなしで30)
#define DIAMETER_A 	30
#define DIAMETER_B 	30
#define DIAMETER_C 	30

//エンコーダ円周
#define ENCODER_CIRCUMFERENCE_A		(DIAMETER_A * PAI)
#define ENCODER_CIRCUMFERENCE_B 	(DIAMETER_B * PAI)
#define ENCODER_CIRCUMFERENCE_C 	(DIAMETER_C * PAI)

#define DUTY_BASE	1000

//自己位置判定の構造体
typedef struct{
	float radian;
	float degree;
	float center_x;
	float center_y;
}Robot_Information;

int g_timer;

float g_degree = 0;
float g_radian = 0;

void Calculate_Information_3tire(Robot_Information	*robot);
void Move(signed int left, signed int right, signed int back);
void Motor_PORT(void);
float rad_deg(float g_radian);
float deg_rad(float g_degree);
double deg180_change(double degree);
void PUT_CHs(char a[50]);
void USB_PUT_CHs(char a[50]);
void PUT_IN(double n);


/******************************************************************************
*	タイトル ： ３輪自己位置判定
*	  関数名 ： Calculate_Information_3tire
*	  戻り値 ： void型
*	   引数1 ： Robot_Information型 *robot
*	  作成者 ： 坂下文彦
*	  作成日 ： 2014/11/21
******************************************************************************/
void Calculate_Information_3tire(Robot_Information	*robot)
{
	int encoder_count_now_a = 0	,encoder_count_now_b = 0,encoder_count_now_c = 0;
	static int encoder_count_old_a = 0,	encoder_count_old_b = 0,	encoder_count_old_c = 0;
	float d_distance_a = 0.0,		d_distance_b = 0.0,		d_distance_c = 0.0;
	float reverse_degree_a = 0.0,	reverse_degree_b = 0.0, reverse_degree_c = 0.0;
	static float movement_a_x = 0.0, movement_a_y = 0.0,
				 movement_b_x = 0.0, movement_b_y = 0.0,
				 movement_c_x = 0.0, movement_c_y = 0.0;
	float radian_a = 0.0,	radian_b = 0.0, radian_c = 0.0 ;


	//車体を真上から見て、車体が反時計回転する方向に動くときのエンコーダカウントを正とする
	encoder_count_now_a = read_value('a');		/*前エンコーダ読み取り*/
	encoder_count_now_b = read_value('b');		/*左エンコーダ読み取り*/
	encoder_count_now_c = read_value('c');		/*右エンコーダ読み取り*/

	//各エンコーダの微小移動距離を算出
	d_distance_a = (encoder_count_now_a - encoder_count_old_a) * (ENCODER_CIRCUMFERENCE_A / PULSE);
	d_distance_b = (encoder_count_now_b - encoder_count_old_b) * (ENCODER_CIRCUMFERENCE_B / PULSE);
	d_distance_c = (encoder_count_now_c - encoder_count_old_c) * (ENCODER_CIRCUMFERENCE_C / PULSE);

	//各エンコーダの微小移動距離からラジアンを求める
	radian_a = d_distance_a / ENCODER_DISTANCE;
	radian_b = d_distance_b / ENCODER_DISTANCE;
	radian_c = d_distance_c / ENCODER_DISTANCE;

	//車体角度を算出
	robot->radian += (radian_a + radian_b + radian_c) / 3;
	if(robot->radian > PAI){
		robot->radian -= 2 * PAI;
	}else if(robot->radian < (-1) * PAI){
		robot->radian += 2 * PAI;
	}
	robot->degree = rad_deg(robot->radian);

	//各エンコーダの微小移動方向からの角度反転
	if(d_distance_a < 0){
		reverse_degree_a = 180.0;
	}
	if(d_distance_b < 0){
		reverse_degree_b = 180.0;
	}
	if(d_distance_c < 0){
		reverse_degree_c = 180.0;
	}

	//各エンコーダの微小移動から求まるｘ、y方向の移動量を計算して2倍する
	movement_a_x += 2.0 * (fabs(d_distance_a) * cos(deg_rad(g_degree + 90.0 + reverse_degree_a)));
	movement_a_y += 2.0 * (fabs(d_distance_a) * sin(deg_rad(g_degree + 90.0 + reverse_degree_a)));
	movement_b_x += 2.0 * (fabs(d_distance_b) * cos(deg_rad(g_degree - 150.0 + reverse_degree_b)));
	movement_b_y += 2.0 * (fabs(d_distance_b) * sin(deg_rad(g_degree - 150.0 + reverse_degree_b)));
	movement_c_x += 2.0 * (fabs(d_distance_c) * cos(deg_rad(g_degree - 30.0 + reverse_degree_c)));
	movement_c_y += 2.0 * (fabs(d_distance_c) * sin(deg_rad(g_degree - 30.0 + reverse_degree_c)));

	//車体中心座標を算出
	robot->center_x = (movement_a_x + movement_b_x + movement_c_x) / 3.0;
	robot->center_y = (movement_a_y + movement_b_y + movement_c_y) / 3.0;

	encoder_count_old_a = encoder_count_now_a;
	encoder_count_old_b = encoder_count_now_b;
	encoder_count_old_c = encoder_count_now_c;
}

/******************************************************************************
*	タイトル ： モーターポート設定
*	  関数名 ： Motor_PORT
*	  戻り値 ： void型
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2014/11/17
******************************************************************************/
void Motor_PORT(void){

	//左ホイール
	Init_port(GPIO_Mode_OUT, GPIOE, GPIO_Pin_5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, GPIOE, GPIO_Pin_11, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_PWM(TIM1, GPIOE, GPIO_Pin_9, DUTY_BASE);
	//右ホイール
	Init_port(GPIO_Mode_OUT, GPIOC, GPIO_Pin_4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, GPIOA, GPIO_Pin_7, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_PWM(TIM1, GPIOB, GPIO_Pin_1, DUTY_BASE);
	//後ホイール
	Init_port(GPIO_Mode_OUT, GPIOB, GPIO_Pin_12, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, GPIOB, GPIO_Pin_10, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_PWM(TIM1, GPIOE, GPIO_Pin_14, DUTY_BASE);

}

/******************************************************************************
*	タイトル ： モーター出力制御
*	  関数名 ： Move
*	  戻り値 ： void型
*	   引数1 ： float型 left		左のモーター		//signed int に変更
*	   引数2 ： float型 right		右のモーター
*	   引数3: float型 back		後のモーター
*	  作成者 ： 須貝聡子
*	  作成日 ： 2014/11/17
******************************************************************************/
void Move(signed int left, signed int right, signed int back){
	const int min_output = 2;
	int per_right = 0;
	int per_left  = 0;
	int per_back  = 0;

	if(fabs(left) <= min_output){
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		GPIO_ResetBits(GPIOE,GPIO_Pin_11);
	}else if(left > 0){
		GPIO_SetBits(GPIOE,GPIO_Pin_5);
		GPIO_ResetBits(GPIOE,GPIO_Pin_11);
	}else if(left < 0){
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		GPIO_SetBits(GPIOE,GPIO_Pin_11);
	}else{
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		GPIO_ResetBits(GPIOE,GPIO_Pin_11);
	}

	if(fabs(right) <= min_output){
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	}else if(right > 0){
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	}else if(right < 0){
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
	}else{
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	}

	if(fabs(back) <= min_output){
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	}else if(back > 0){
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	}else if(back < 0){
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_10);
	}else{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	}

	//％から実際に代入できる値へ
	per_left  = (int)((fabs( left) * (DUTY_BASE/100)) + 0.5);
	per_right = (int)((fabs(right) * (DUTY_BASE/100)) + 0.5);
	per_back  = (int)((fabs( back) * (DUTY_BASE/100)) + 0.5);

	//左出力値
	if(per_left == 0){
		per_left = 1;
	}else if(per_left >= DUTY_BASE){
		per_left = DUTY_BASE - 1;
	}

	//右出力値
	if(per_right == 0){
		per_right = 1;
	}else if(per_right >= DUTY_BASE){
		per_right = DUTY_BASE - 1;
	}

	//後出力値
	if(per_back == 0){
		per_back = 1;
	}else if(per_back >= DUTY_BASE){
		per_back = DUTY_BASE - 1;
	}

	Set_duty(TIM1,1,per_left);		//左タイヤ出力
	Set_duty(TIM1,3,per_right);		//右タイヤ出力
	Set_duty(TIM1,4,per_back);		//後タイヤ出力

//	TIM_SetCompare1(TIM4,per_left);		//左タイヤ出力確認(LED4)
//	TIM_SetCompare3(TIM4,per_right);	//右タイヤ出力確認(LED5)
//	TIM_SetCompare4(TIM4,per_back);		//後タイヤ出力確認(LED6)

}

/******************************************************************************
*	タイトル ： radianからdegreeに変換する
*	  関数名 ： rad_deg
*	  戻り値 ： int型
*	   引数1 ： double型 radian  ラジアン表記の角度
*	  作成者 ： 須貝聡子
*	  作成日 ： 2014/06/26
******************************************************************************/
float rad_deg(float g_radian)
{
//	double degree;
	g_degree = (180 * g_radian) / PAI;
	return g_degree;
}

/******************************************************************************
*	タイトル ： degreeからradianに変換する
*	  関数名 ： deg_rad
*	  戻り値 ： int型
*	   引数1 ： double型 degree  ディグリー表記の角度
*	  作成者 ： 須貝聡子
*	  作成日 ： 2014/06/26
******************************************************************************/
float deg_rad(float g_degree)
{
//	double radian;
	g_radian = (PAI * g_degree) / 180;
	return g_radian;
}

/******************************************************************************
*	タイトル ： 角度の範囲を指定する
*	  関数名 ： deg180_change
*	  戻り値 ： double型
*	   引数1 ： double型 degree  ディグリー表記の角度
*	  作成者 ： 須貝聡子
*	  作成日 ： 2014/06/28
******************************************************************************/
double deg180_change(double degree)
{
	signed int x;
	x = degree / 360;
	       degree = degree - 360 * x;
	       	if(degree >= 180){
		       degree = degree - 360;
		       x = 0;

	       	}
		if(degree < -180){
		       degree = degree + 360;
		       x = 0;

	       }
		return degree;
}

/******************************************************************************
*	タイトル ： 文字列を出力する
*	  関数名 ： PUT_CHs
*	  戻り値 ： void型
*	   引数1 ： char型 a[100]  ここに入れた値が出力される
*	  作成者 ： 須貝
*	  作成日 ： 2014/06/25
******************************************************************************/
void PUT_CHs(char a[100])
{
	int i;
	char b[100] = {0};

	sprintf(b,"%s",a);
	for(i=0; b[i] != 0 && i<100; i++){
		USART_SendData(USART3,b[i]);
	}
}

/******************************************************************************
*	タイトル ： USBで文字列を出力する
*	  関数名 ： USB_PUT_CHs
*	  戻り値 ： void型
*	   引数1 ： char型 a[100]  ここに入れた値が出力される
*	  作成者 ： 須貝
*	  作成日 ： 2014/11/18
******************************************************************************/
void USB_PUT_CHs(char a[100])
{
	int i;
	char b[100] = {0};

	sprintf(b,"%s",a);
	for(i=0; b[i] != 0 && i<100; i++){
		usb_put_char(b[i]);
	}
}

/******************************************************************************
*	タイトル ： 数値を出力する
*	  関数名 ： PUT_IN
*	  戻り値 ： void型
*	   引数1 ： double型 n  ここに入れた数値が出力される
*	  作成者 ： 須貝
*	  作成日 ： 2014/06/25
******************************************************************************/
void PUT_IN(double n)
{
	int i;
	char b[100] = {0};

	sprintf(b,"%0.2lf",n);
	for(i=0; b[i] != 0 && i<100; i++){
		usb_put_char(b[i]);
	}
}

int main(void)
{

	SystemInit();
	Init_SysTick(0.001);
//	Init_port(GPIO_Mode_OUT, GPIOD, GPIO_Pin_13, GPIO_PuPd_NOPULL, GPIO_OType_PP);
//	Init_PWM(TIM4, GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, 1000);
//	Init_encoder(TIM2, GPIOA, GPIO_Pin_0 | GPIO_Pin_1);

//	Init_ADC1(GPIOA, GPIO_Pin_5);
	Init_USART(USART3, 115200, GPIOD, GPIO_Pin_8, GPIOD, GPIO_Pin_9);
	Init_usb();
//	Init_port(GPIO_Mode_OUT, GPIOA, GPIO_Pin_15, GPIO_PuPd_UP, GPIO_OType_PP);		//Highにするとエンコーダ値をリセットできる
//	Init_port(GPIO_Mode_IN, GPIOC, GPIO_Pin_13, GPIO_PuPd_DOWN, GPIO_OType_PP);		//スタートスイッチ
//	Init_port(GPIO_Mode_OUT, GPIOE, GPIO_Pin_1, GPIO_PuPd_UP, GPIO_OType_PP);		//ブザー
//	Motor_PORT();
//	Calculate_Information_3tire(Robot_Information	*robot);		//radian, degree, c_x, c_y

//	signed int left = 0;
//	signed int right = 0;
//	signed int back = 0;

//	int count = 0;

	float encoder_a = 0;
	float encoder_b = 0;
	float encoder_c = 0;

//	int n = 1;

//		while(n){
//			if(SWITCH == 1){
//				n = 0;
//			}
//		}
		while(1){
			if(g_timer >= 5){
				g_timer = 0;

//				GPIO_ResetBits(GPIOA,GPIO_Pin_15);

//				write_value('a',10);

				encoder_a = read_value('a');
				encoder_b = read_value('b');
				encoder_c = read_value('c');

				f_print(USB_PC, "encoder_a", encoder_a);
				f_print(USB_PC, "encoder_b", encoder_b);
				f_print(USB_PC, "encoder_c", encoder_c);
				put_enter(USB_PC);

				//USB通信テスト
				//usb_put_char(USART_ReceiveData(USART3));
				//USB_PUT_CHs("coming\n");
				//PUT_IN(70);
				//USB_PUT_CHs("\n");

				//Move(left, right, back);
\
			}
		}
		return 0;
}

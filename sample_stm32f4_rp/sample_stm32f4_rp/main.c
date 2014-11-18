
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

#include <stdio.h>

#define PAI 			3.14
#define PULSE 			400
#define ROBO_LENGTH 	87.5
#define DIAMETER_LEFT 	30
#define DIAMETER_RIGHT 	30
#define DIAMETER_BACK 	30

#define DUTY_BASE	1000

void Move(float left, float right, float back);
void Motor_PORT(void);

/******************************************************************************
*	タイトル ： エンコーダーポート設定
*	  関数名 ： encoder_PORT
*	  戻り値 ： void型
*	    引数 ： なし
*	  作成者 ： 須貝聡子
*	  作成日 ： 2014/11/17
******************************************************************************/
void Encoder_PORT(void){

	//左エンコーダー
	Init_encoder(TIM4, GPIOB, GPIO_Pin_6 | GPIO_Pin_7);
	//右エンコーダー
	Init_encoder(TIM2, GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
	//後エンコーダー
	Init_encoder(TIM3, GPIOC, GPIO_Pin_6 | GPIO_Pin_7);

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
	Init_port(GPIO_Mode_OUT, GPIOB, GPIO_Pin_12, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, GPIOB, GPIO_Pin_10, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_PWM(TIM1, GPIOE, GPIO_Pin_14, DUTY_BASE);
	//右ホイール
	Init_port(GPIO_Mode_OUT, GPIOC, GPIO_Pin_4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, GPIOA, GPIO_Pin_7, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_PWM(TIM3, GPIOB, GPIO_Pin_1, DUTY_BASE);
	//後ホイール
	Init_port(GPIO_Mode_OUT, GPIOC, GPIO_Pin_5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, GPIOA, GPIO_Pin_6, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_PWM(TIM3, GPIOB, GPIO_Pin_0, DUTY_BASE);

}

/******************************************************************************
*	タイトル ： モーター出力制御
*	  関数名 ： Move
*	  戻り値 ： void型
*	   引数1 ： float型 left		左のモーター
*	   引数2 ： float型 right		右のモーター
*	   引数3: float型 back		後のモーター
*	  作成者 ： 須貝聡子
*	  作成日 ： 2014/11/17
******************************************************************************/
void Move(float left, float right, float back){
	const int min_output = 2;
	int per_right = 0;
	int per_left  = 0;
	int per_back  = 0;

	if(fabs(left) <= min_output){
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	}else if(left > 0){
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	}else if(left < 0){
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_10);
	}else{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);
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
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	}else if(back > 0){
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	}else if(back < 0){
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
	}else{
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	}

	//％から実際に代入できる値へ
	per_right = (int)((fabs(right) * (DUTY_BASE/100)) + 0.5);
	per_left  = (int)((fabs( left) * (DUTY_BASE/100)) + 0.5);
	per_back  = (int)((fabs( back) * (DUTY_BASE/100)) + 0.5);

	//右出力値
	if(per_right == 0){
		per_right = 1;
	}else if(per_right >= DUTY_BASE){
		per_right = DUTY_BASE - 1;
	}

	//左出力値
	if(per_left == 0){
		per_left = 1;
	}else if(per_left >= DUTY_BASE){
		per_left = DUTY_BASE - 1;
	}

	//後出力値
	if(per_back == 0){
		per_back = 1;
	}else if(per_back >= DUTY_BASE){
		per_back = DUTY_BASE - 1;
	}

	Set_duty(TIM1,4,per_left);		//左タイヤ出力
	Set_duty(TIM3,4,per_right);		//右タイヤ出力
	Set_duty(TIM3,3,per_back);		//後タイヤ出力

	TIM_SetCompare1(TIM4,per_left);		//左タイヤ出力確認(LED4)
	TIM_SetCompare3(TIM4,per_right);	//右タイヤ出力確認(LED5)
	TIM_SetCompare4(TIM4,per_back);		//後タイヤ出力確認(LED6)
}

/******************************************************************************
*	タイトル ： radからdegに変換する
*	  関数名 ： rad_deg
*	  戻り値 ： int型
*	   引数1 ： double型 rad  ラジアン表記の角度
*	  作成者 ： 須貝聡子
*	  作成日 ： 2014/06/26
******************************************************************************/
double rad_deg(double rad)
{
	double deg;
	deg = (180 * rad) / PAI;
	return deg;
}

/******************************************************************************
*	タイトル ： degからradに変換する
*	  関数名 ： deg_rad
*	  戻り値 ： int型
*	   引数1 ： double型 deg  ディグリー表記の角度
*	  作成者 ： 須貝聡子
*	  作成日 ： 2014/06/26
******************************************************************************/
double deg_rad(double deg)
{
	double rad;
	rad = (PAI * deg) / 180;
	return rad;
}

/******************************************************************************
*	タイトル ： 角度の範囲を指定する
*	  関数名 ： deg180_change
*	  戻り値 ： double型
*	   引数1 ： double型 deg  ディグリー表記の角度
*	  作成者 ： 須貝聡子
*	  作成日 ： 2014/06/28
******************************************************************************/
double deg180_change(double deg)
{
	signed int x;
	x = deg / 360;
	       deg = deg - 360 * x;
	       	if(deg >= 180){
		       deg = deg - 360;
		       x = 0;

	       	}
		if(deg < -180){
		       deg = deg + 360;
		       x = 0;

	       }
		return deg;
}

/******************************************************************************
*	タイトル ： 文字列を出力する
*	  関数名 ： PUT_CHs
*	  戻り値 ： void型
*	   引数1 ： char型 a[100]  ここに入れた値が出力される
*	  作成者 ： 須貝
*	  作成日 ： 2014/06/25
******************************************************************************/
void PUT_CHs(char a[50])
{
	int i;
	char b[50] = {0};

	sprintf(b,"%s",a);
	for(i=0; b[i] != 0 && i<50; i++){
		USART_SendData(USART1,b[i]);
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
void USB_PUT_CHs(char a[50])
{
	int i;
	char b[50] = {0};

	sprintf(b,"%s",a);
	for(i=0; b[i] != 0 && i<50; i++){
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
	sprintf(b,"%0.4lf",n);
	for(i=0; b[i] != 0 && i<100; i++){
		usb_put_char(b[i]);
	}
}

int main(void)
{

	SystemInit();
	Init_SysTick(0.001);
	Init_port(GPIO_Mode_OUT, GPIOD, GPIO_Pin_13, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_ADC1(GPIOC, GPIO_Pin_0);
	Init_PWM(TIM4, GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15, 1000);
	Init_USART(USART1, 115200, GPIOB, GPIO_Pin_6, GPIOB, GPIO_Pin_7);
	Init_encoder(TIM2, GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
	Init_usb();

	Encoder_PORT();
	Motor_PORT();

	float left = 0;
	float right = 0;
	float back = 0;

	while(1){

		if(g_timer >= 5){
			g_timer = 0;

			//USB通信テスト
			usb_put_char('A');
			USB_PUT_CHs("coming\n");

			//USARTテスト
			PUT_CHs("command");
			USART_SendData(USART1,'B');

			if(USART_ReceiveData(USART1)){
				left = 1000;
				right = 0;
			}else{
				left = 0;
				right = 100;
			}

//			left = 1000;
//			right = 500;
			back = 90;

			Move(left, right, back);

		}
	}

		return 0;
}

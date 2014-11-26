
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
*	�^�C�g�� �F �G���R�[�_�[�|�[�g�ݒ�
*	  �֐��� �F encoder_PORT
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F �{�L���q
*	  �쐬�� �F 2014/11/17
******************************************************************************/
void Encoder_PORT(void){

	//���G���R�[�_�[
	Init_encoder(TIM4, GPIOB, GPIO_Pin_6 | GPIO_Pin_7);
	//�E�G���R�[�_�[
	Init_encoder(TIM2, GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
	//��G���R�[�_�[
	Init_encoder(TIM3, GPIOC, GPIO_Pin_6 | GPIO_Pin_7);

}

/******************************************************************************
*	�^�C�g�� �F ���[�^�[�|�[�g�ݒ�
*	  �֐��� �F Motor_PORT
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F �{�L���q
*	  �쐬�� �F 2014/11/17
******************************************************************************/
void Motor_PORT(void){

	//���z�C�[��
	Init_port(GPIO_Mode_OUT, GPIOB, GPIO_Pin_12, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, GPIOB, GPIO_Pin_10, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_PWM(TIM1, GPIOE, GPIO_Pin_14, DUTY_BASE);
	//�E�z�C�[��
	Init_port(GPIO_Mode_OUT, GPIOC, GPIO_Pin_4, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, GPIOA, GPIO_Pin_7, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_PWM(TIM3, GPIOB, GPIO_Pin_1, DUTY_BASE);
	//��z�C�[��
	Init_port(GPIO_Mode_OUT, GPIOC, GPIO_Pin_5, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_port(GPIO_Mode_OUT, GPIOA, GPIO_Pin_6, GPIO_PuPd_NOPULL, GPIO_OType_PP);
	Init_PWM(TIM3, GPIOB, GPIO_Pin_0, DUTY_BASE);

}

/******************************************************************************
*	�^�C�g�� �F ���[�^�[�o�͐���
*	  �֐��� �F Move
*	  �߂�l �F void�^
*	   ����1 �F float�^ left		���̃��[�^�[
*	   ����2 �F float�^ right		�E�̃��[�^�[
*	   ����3: float�^ back		��̃��[�^�[
*	  �쐬�� �F �{�L���q
*	  �쐬�� �F 2014/11/17
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

	//��������ۂɑ���ł���l��
	per_right = (int)((fabs(right) * (DUTY_BASE/100)) + 0.5);
	per_left  = (int)((fabs( left) * (DUTY_BASE/100)) + 0.5);
	per_back  = (int)((fabs( back) * (DUTY_BASE/100)) + 0.5);

	//�E�o�͒l
	if(per_right == 0){
		per_right = 1;
	}else if(per_right >= DUTY_BASE){
		per_right = DUTY_BASE - 1;
	}

	//���o�͒l
	if(per_left == 0){
		per_left = 1;
	}else if(per_left >= DUTY_BASE){
		per_left = DUTY_BASE - 1;
	}

	//��o�͒l
	if(per_back == 0){
		per_back = 1;
	}else if(per_back >= DUTY_BASE){
		per_back = DUTY_BASE - 1;
	}

	Set_duty(TIM1,4,per_left);		//���^�C���o��
	Set_duty(TIM3,4,per_right);		//�E�^�C���o��
	Set_duty(TIM3,3,per_back);		//��^�C���o��

	TIM_SetCompare1(TIM4,per_left);		//���^�C���o�͊m�F(LED4)
	TIM_SetCompare3(TIM4,per_right);	//�E�^�C���o�͊m�F(LED5)
	TIM_SetCompare4(TIM4,per_back);		//��^�C���o�͊m�F(LED6)
}

/******************************************************************************
*	�^�C�g�� �F rad����deg�ɕϊ�����
*	  �֐��� �F rad_deg
*	  �߂�l �F int�^
*	   ����1 �F double�^ rad  ���W�A���\�L�̊p�x
*	  �쐬�� �F �{�L���q
*	  �쐬�� �F 2014/06/26
******************************************************************************/
double rad_deg(double rad)
{
	double deg;
	deg = (180 * rad) / PAI;
	return deg;
}

/******************************************************************************
*	�^�C�g�� �F deg����rad�ɕϊ�����
*	  �֐��� �F deg_rad
*	  �߂�l �F int�^
*	   ����1 �F double�^ deg  �f�B�O���[�\�L�̊p�x
*	  �쐬�� �F �{�L���q
*	  �쐬�� �F 2014/06/26
******************************************************************************/
double deg_rad(double deg)
{
	double rad;
	rad = (PAI * deg) / 180;
	return rad;
}

/******************************************************************************
*	�^�C�g�� �F �p�x�͈̔͂��w�肷��
*	  �֐��� �F deg180_change
*	  �߂�l �F double�^
*	   ����1 �F double�^ deg  �f�B�O���[�\�L�̊p�x
*	  �쐬�� �F �{�L���q
*	  �쐬�� �F 2014/06/28
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
*	�^�C�g�� �F ��������o�͂���
*	  �֐��� �F PUT_CHs
*	  �߂�l �F void�^
*	   ����1 �F char�^ a[100]  �����ɓ��ꂽ�l���o�͂����
*	  �쐬�� �F �{�L
*	  �쐬�� �F 2014/06/25
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
*	�^�C�g�� �F USB�ŕ�������o�͂���
*	  �֐��� �F USB_PUT_CHs
*	  �߂�l �F void�^
*	   ����1 �F char�^ a[100]  �����ɓ��ꂽ�l���o�͂����
*	  �쐬�� �F �{�L
*	  �쐬�� �F 2014/11/18
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
*	�^�C�g�� �F ���l���o�͂���
*	  �֐��� �F PUT_IN
*	  �߂�l �F void�^
*	   ����1 �F double�^ n  �����ɓ��ꂽ���l���o�͂����
*	  �쐬�� �F �{�L
*	  �쐬�� �F 2014/06/25
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

			//USB�ʐM�e�X�g
			usb_put_char('A');
			USB_PUT_CHs("coming\n");

			//USART�e�X�g
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


#ifndef  CONFIG_PWM_H
#define CONFIG_PWM_H

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "system_stm32f4xx.h"

#include "config_port.h"
#include "name_converter.h"

/*//PWM�̎g�p��

Init_PWM(TIM4,GPIOD,GPIO_Pin_13,10000);
TIM4��PWM�ɐݒ肵�APD13����10000Hz��PWM�g���o���B

Set_duty(TIM4,2,0.5);
TIM4��ch2��duty��50%�ɐݒ�B
duty���float�^��0-1�B�����_�Ŏw��B

GPIO��pin�ԍ��ƃ`�����l���Ɋւ��Ă�STM32F407�̃f�[�^�V�[�g(DocID022152 Rev 4)��60�y�[�W�ȍ~�ł�����Ƃ����B

#define LED3PWMSET TIM4,GPIOD,GPIO_Pin_13
#define LED3PWM TIM4,2
���Đ錾����

Init_PWM(LED3PWMSET,10000);
Set_duty(LED3PWM,0.1);

���Ă�����@������񂾂��ǁA�֐��̈����̐������������邩��C���������B
�����Ȑl������񂶂�Ȃ����Ȃ��Ďv���ĕ�������A���ۂɂ����B

Init_PWM(TIM4,GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15,10000);
���Ă��Ƃ��ł���B

Init_PWM�֐��͎��g���ݒ肪���܂������Ȃ������Ƃ���1���Ԃ��Ă���悤�ɂȂ��Ă�B

#define PRINTF_AVAILABLE ���w�b�_�t�@�C���ɒǉ�����ƁAprintf��ݒ肵�Ă���ΐݒ�̉ߒ���������B
*/
void  Set_duty(TIM_TypeDef* TIMx,uint8_t ch,float duty);										//�f���[�e�B��̐ݒ�
int Init_PWM(TIM_TypeDef * TIMx,GPIO_TypeDef *GPIOx,uint16_t pin,int frequency);	//PWM�g�`�̐ݒ�

#endif//CONFIG_PWM_H

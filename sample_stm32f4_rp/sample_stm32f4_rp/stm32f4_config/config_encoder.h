
#ifndef CONFIG_ENCODER_H
#define CONFIG_ENCODER_H

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"

#include "name_converter.h"
#include "config_port.h"

void Init_encoder(TIM_TypeDef *tim,  GPIO_TypeDef *port, uint16_t pin);

void TIM1_UP_TIM10_IRQHandler(void);

void TIM2_IRQHandler(void);

void TIM3_IRQHandler(void);

void TIM4_IRQHandler(void);

void TIM5_IRQHandler(void);

void TIM8_UP_TIM13_IRQHandler(void);

int tim1_count( void );

int tim2_count( void );

int tim3_count( void );

int tim4_count( void );

int tim5_count( void );

int tim8_count( void );

/* �g���� */
/*Init_encoder���Ăяo�������Ɏg�������@�^�C�}�[�A�|�[�g�A�s���@������ƃG���R�[�_�̐ݒ肪�ł��܂��B*/
/*�G���R�[�_�̃J�E���g�l�����������́A timx_count ���Ăяo���ƒl�����܂��B(x �͐���)*/
/*TIMx: where x can be 1, 2, 3, 4, 5, 8, 9 or 12 to select the TIM*/

#endif

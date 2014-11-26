
#ifndef CONFIG_USART_H
#define CONFIG_USART_H

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

#include "config_port.h"
#include "name_converter.h"


/*USART��ݒ肷��֐�
USART�ԍ��A�{�[���[āA�s�w���|�[�g�E�s���A�q�w���|�[�g�E�s���������Ƃ���B

�g�p��)USART1��PA1(RX)PA2(TX)�@�{�[���[�g115200��ݒ肵�����ꍇ
Init_USART(USART1,115200,GPIOA,GPIO_pin_1,GPIOA,GPIO_pin_2)*/
void Init_USART(USART_TypeDef *USARTx,unsigned int baudrate, GPIO_TypeDef *GPIOx_TX ,uint16_t pin_TX, GPIO_TypeDef *GPIOx_RX, uint16_t pin_RX);


/*USART�����݂��N�������Ƃ�����֐��B
�Ăяo���K�v�͂Ȃ��B*/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);


#endif

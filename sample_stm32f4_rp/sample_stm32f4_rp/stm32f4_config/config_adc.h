
#ifndef  CONFIG_ADC_H
#define CONFIG_ADC_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"

#include "config_port.h"
#include "name_converter.h"

uint8_t Select_ADC_channel(GPIO_TypeDef *GPIOx, uint16_t pin);		
void Init_ADC1(GPIO_TypeDef *GPIOx, uint16_t pin);
short get_ADC1_value(unsigned short ch);

/*�֐�����*/

/*Select_ADC_channel(GPIO_TypeDef *GPIOx, uint16_t pin)*/
/*�w�肵���|�[�g�ƃs���ɑΉ�����ADC_Channel��Ԃ�*/
/*�g�p��
	ADC_channel = Select_ADC_channel(GPIOA, GPIO_Pin_5);*/


/*Init_ADC1(GPIO_TypeDef *GPIOx, uint16_t pin,short *ADC_converted_value)*/
/*ADC1�̏����ݒ�*/
/*�g�p��
	Init_ADC1(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3, &ad_value[3]);
	���ݒ�ł���̂�1�̃|�[�g�̂݁B�s���͕����Ή�*/

/*get_ADC1_value(unsigned short ch)*/
/*�w�肵���`�����l����ADC1�̒l�𓾂�*/
/*�g�p��
	adc_value = get_ADC1_value(3)
	���`�����l����0����7�܂�*/

#endif

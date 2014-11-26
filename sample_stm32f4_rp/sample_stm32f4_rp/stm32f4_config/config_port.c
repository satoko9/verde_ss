#include "config_port.h"

/******************************************************************************
*	�^�C�g�� �F �|�[�g�̐ݒ�i�Œ�j
*	  �֐��� �F Init_port
*	  �߂�l �F void�^						�Ȃ�
*	   ����1 �F GPIOMode_TypeDef�^	mode	���[�h�̎w��
*	   ����2 �F GPIO_TypeDef*�^		port	�|�[�g�̎w��
*	   ����3 �F uint16_t�^			pin		�s���̎w��
*	   ����4 �F GPIOPuPd_TypeDef�^	pupd	�v���A�b�v/�_�E���̎w��
*	   ����5 �F GPIOOType_TypeDef�^	otype	�o�̓^�C�v�̎w��
*	  �쐬�� �F �ː�
*	  �쐬�� �F 2014/11/10
******************************************************************************/
void Init_port(GPIOMode_TypeDef mode,GPIO_TypeDef *port,uint16_t pin,GPIOPuPd_TypeDef pupd,GPIOOType_TypeDef otype){
	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO�������̂��߂̍\����

	//���W���[���X�g�b�v�̉���
	if(port == GPIOA){
	#ifndef RCC_AHB1Periph_GPIOA_SETEND
		#define RCC_AHB1Periph_GPIOA_SETEND
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	#endif
	}
	#ifndef RCC_AHB1Periph_GPIOB_SETEND
	else if(port == GPIOB){
		#define RCC_AHB1Periph_GPIOB_SETEND
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	}
	#endif
	#ifndef RCC_AHB1Periph_GPIOC_SETEND
	else if(port == GPIOC){
		#define RCC_AHB1Periph_GPIOC_SETEND
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	}
	#endif
	#ifndef RCC_AHB1Periph_GPIOD_SETEND
	else if(port == GPIOD){
		#define RCC_AHB1Periph_GPIOD_SETEND
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	}
	#endif
	#ifndef RCC_AHB1Periph_GPIOE_SETEND
	else if(port == GPIOE){
		#define RCC_AHB1Periph_GPIOE_SETEND
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	}
	#endif

	GPIO_StructInit(&GPIO_InitStructure);											//�������p�\���̂Ƀp�����[�^���Z�b�g���Ă������߁A�������񏉊��l�ɖ߂�
	GPIO_InitStructure.GPIO_Pin = pin;												//�ݒ肷��s�����w�肷��

	GPIO_InitStructure.GPIO_Mode = mode;										//�s���̃��[�h�ݒ�
	GPIO_InitStructure.GPIO_OType = otype;										//�o�̓^�C�v�ݒ�
	GPIO_InitStructure.GPIO_PuPd = pupd;											//�o�̓|�[�g���v�b�V���v���܂��̓I�[�v���h���C���ɐݒ�


	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//GPIO�̃X�s�[�h��100MHz�i�ō����j�ɐݒ肷��
	GPIO_Init(port, &GPIO_InitStructure);											//PORT�ݒ����

	if(mode == GPIO_Mode_OUT)	GPIO_ResetBits(port,pin);			//�|�[�g�̃��Z�b�g
}


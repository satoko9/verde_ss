
#ifndef CONFIG_SYSTICK_H
#define CONFIG_SYSTICK_H
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
extern int g_timer;

void SysTick_Handler(void);	//���荞�݃n���h��
void Init_SysTick(float time);	//���荞�݃^�C�}�[�̏����ݒ�

#endif // !CONFIG_SYSTICK_H


/***********************�d�l����************************

void SysTick_Handler(void);	//���荞�݃n���h��
	�C��[ms]���Ɋ��荞�݂ɂ���ČĂяo����郋�[�`��
	���̊֐����ɔC�ӂ̊��荞�ݏ����������悤
	�C��[ms]���Ȃ̂ŏ������������Ȃ��悤�ɒ���


void Init_SysTick(unsigned float time);	//���荞�݃^�C�}�[�̏����ݒ�@
	���荞�ݎ����̐ݒ�֐�
	���荞�݂Ɏg�p�����������������Ɏw�肵�g����


******************************************************/

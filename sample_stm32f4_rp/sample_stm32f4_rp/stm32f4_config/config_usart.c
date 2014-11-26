#include "config_usart.h"
signed int g_cnt1 = 0;
signed int g_cnt2 = 0;
signed int g_cnt3 = 0;

/******************************************************************************
*	�^�C�g�� �F USART1�����݊֐�
*	  �֐��� �F USART1_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F �Έ�x�j
*	  �쐬�� �F 2014/11/12
******************************************************************************/
void USART1_IRQHandler(void){
		g_cnt1++;
}

/******************************************************************************
*	�^�C�g�� �F USART2�����݊֐�
*	  �֐��� �F USART2_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F �Έ�x�j
*	  �쐬�� �F 2014/11/12
******************************************************************************/
void USART2_IRQHandler(void){
		g_cnt2++;
}

/******************************************************************************
*	�^�C�g�� �F USART3�����݊֐�
*	  �֐��� �F USART3_IRQHandler
*	  �߂�l �F void�^
*	    ���� �F �Ȃ�
*	  �쐬�� �F �Έ�x�j
*	  �쐬�� �F 2014/11/12
******************************************************************************/
void USART3_IRQHandler(void){
		g_cnt3++;
}

/******************************************************************************
*	�^�C�g�� �F USART�ݒ�
*	  �֐��� �F Init_USART
*	   ����1 �F USART_TypeDef�^ *USARTx  USART�ԍ�
*	   ����2 �F unsigned int�^ baudrate  �{�[���[�g
*	   ����3 �F GPIO_TypeDef�^ *GPIOx_TX  TX�|�[�g
*	   ����4 �F uint16_t�^ pin_TX  TX�s��
*	   ����5 �F GPIO_TypeDef�^ *GPIOx_RX  RX�|�[�g
*	   ����6 �F uint16_t�^ pin_RX  RX�s��
*	  �쐬�� �F �Έ�x�j
*	  �쐬�� �F 2014/11/12
******************************************************************************/
void Init_USART(USART_TypeDef *USARTx,unsigned int baudrate, GPIO_TypeDef *GPIOx_TX ,uint16_t pin_TX, GPIO_TypeDef *GPIOx_RX, uint16_t pin_RX){
	//�\���̕ϐ���錾
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStructure;

	//���W���[���X�g�b�v��Ԃ̉���
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_PeriphClock_USART(USARTx);
	//GPIO�̐ݒ�
	Init_port(GPIO_Mode_AF,GPIOx_TX,pin_TX,GPIO_PuPd_NOPULL,GPIO_OType_PP);
	Init_port(GPIO_Mode_AF,GPIOx_RX,pin_RX,GPIO_PuPd_NOPULL,GPIO_OType_PP);

	//PIN���I���^�l�B�e�u�t�@���N�V�����Ɋ��蓖��

	GPIO_PinAFConfig(GPIOx_TX, Pin_select_source(pin_TX), GPIO_af_USART_select(USARTx));//USART1 TX/PB6
	GPIO_PinAFConfig(GPIOx_RX, Pin_select_source(pin_RX), GPIO_af_USART_select(USARTx));//USART1 RX/PB7


	//USART1�̐ݒ�
	USART_InitStructure.USART_BaudRate 				= baudrate;							//�{�[���[�g�̐ݒ�
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;				//�r�b�g��
	USART_InitStructure.USART_StopBits 				= USART_StopBits_1;					//�X�g�b�v�r�b�g�̒���
	USART_InitStructure.USART_Parity 				= USART_Parity_No;					//�p���e�B�̗L��
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;	//�n�[�h�E�F�A�t���[����̗L��
	USART_InitStructure.USART_Mode 					= USART_Mode_Rx | USART_Mode_Tx;	//���M��M�̑I��
	USART_Init(USARTx, &USART_InitStructure);											//USART1�̐ݒ�
	USART_Cmd(USARTx, ENABLE);															//USART1���Ӊ�H�̗L����
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);										//USART1���Ӊ�H�̊����ݗL����

	//���荞�ݐݒ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);							//�D��x�̃r�b�g�ݒ�
	NVIC_InitStructure.NVIC_IRQChannel 						= USART_irqn_select(USARTx);	//�L��������IRQ�`�����l���̎w��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 2;			//���荞�݂̗D�揇�ʁi�O���[�v�j�̎w��B0���ŗD��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 			= 0;			//���荞�݂̗D�揇��(�T�u)�̎w��B0���ŗD��
	NVIC_InitStructure.NVIC_IRQChannelCmd 					= ENABLE;		//���荞�݂̗L����
	NVIC_Init(&NVIC_InitStructure);											//���荞�ݐݒ�
}

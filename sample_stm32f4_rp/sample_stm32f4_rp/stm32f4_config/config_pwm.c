#include "config_pwm.h"

#ifdef PRINTF_AVAILABLE
#include <stdio.h>
#endif
#define PERIOD_LIMIT						65535	//�ݒ�ł���period�̍ő�l
#define PERIOD_UNDER_LIMIT			100		//�ݒ肷��period�̍ŏ��l
#define PRESCALER_LIMIT					65535	//�ݒ�ł���v���X�P�[���̍ő�l
#define PRESCALER_UNDER_LIMIT		1			//�ݒ�ł���v���X�P�[���̍ŏ��l
#define FREQUENCY_UNDER_LIMIT	1			//�ݒ�ł�����g���̍ŏ��l
#define RCC_TIMPRE			((MY_RCC->DCKCFGR>>24)&1)			//RCC�̕���
#define MY_RCC                ((My_RCC_TypeDef *) RCC_BASE)		//�i�J���ݒ肵��RCC�̃A�h���X

//RCC�̃A�h���X�̍\����
typedef struct
{
  __IO uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
  __IO uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
  __IO uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
  __IO uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
  __IO uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
  __IO uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  __IO uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  __IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
  __IO uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  __IO uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  __IO uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  __IO uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  __IO uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  __IO uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  __IO uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  __IO uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  __IO uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  __IO uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  __IO uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
  __IO uint32_t PLLSAICFGR;    /*!< 6.3.24 RCC PLL configuration register,                       Address offset: 0x88 */
  __IO uint32_t DCKCFGR;	   /*!< 6.3.25 RCC Dedicated Clock Configuration Register,           Address offset: 0x8c */
} My_RCC_TypeDef;

/******************************************************************************
*	�^�C�g�� �F PWM��duty��̐ݒ�
*	  �֐��� �F Set_duty
*	  �߂�l �F void�^
*	   ����1 �F TIM_TypeDef*�^ TIMx  TIM
*	   ����2 �F uint8_t�^ ch  TIM�̃`�����l��1-4
*	   ����3 �F float�^ duty  duty���0-1�œ���
*	  �쐬�� �F �i�J �q�M
*	  �쐬�� �F 2014/11/10
******************************************************************************/
void  Set_duty(TIM_TypeDef* TIMx,uint8_t ch,float duty){
	switch(ch){
	case 1:
		TIMx->CCR1=TIMx->ARR*duty;
		break;
	case 2:
		TIMx->CCR2=TIMx->ARR*duty;
		break;
	case 3:
		TIMx->CCR3=TIMx->ARR*duty;
		break;
	case 4:
		TIMx->CCR4=TIMx->ARR*duty;
		break;
	default:
		break;
	}
}

/******************************************************************************
*	�^�C�g�� �F PWM�����ݒ�
*	  �֐��� �F Init_PWM
*	  �߂�l �F int�^ 0:�ݒ�ł��� 1:�ݒ�ł��Ȃ�
*	   ����1 �F TIM_TypeDef *�^ TIMx  TIMx TIM�̃|�C���^
*	   ����2 �F GPIO_TypeDef�^ *GPIOx  GPIOx GPIO�̃|�C���^
*	   ����3 �F uint16_t�^ pin  GPIO_Pin_x PIN�̐ݒ�
*	   ����4 �F int�^ frequency  PWM���g��[Hz](����)
*	  �쐬�� �F �i�J �q�M
*	  �쐬�� �F 2014/11/10
******************************************************************************/
int Init_PWM(TIM_TypeDef * TIMx,GPIO_TypeDef *GPIOx,uint16_t pin,int frequency)//�G���[�������1�A�Ȃ����0��return����
{
	long TIM_clock=0;
	int prescaler=0;
	int period=0;
	int calc_retry_flag=1;
	//float error_ratio=0;

	unsigned short i = 0;
	Pin_t	pin_state;//

	//�V�X�e���N���b�N��RCC_Clocks�Ŏ擾
	SystemCoreClockUpdate();
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);

	//TIM�̃N���b�N�̎擾
	if((TIM2<=TIMx&&TIMx<=TIM7)||(TIM12<=TIMx&&TIMx<=TIM14)){
		TIM_clock=RCC_Clocks.PCLK1_Frequency*((RCC_TIMPRE+1)*2);	//PCLK1��TIM�v���X�P�[���{������TIM2-7,12-14�̃N���b�N���o�Ă���
	}else{
		TIM_clock=RCC_Clocks.PCLK2_Frequency*((RCC_TIMPRE+1)*2);	//PCLK2��TIM�v���X�P�[���{�������̂�ȊO�̃N���b�N���o�Ă���
	}
#ifdef PRINTF_AVAILABLE
	printf("Init_PWM() start.\nTIM_clock:%d,\n",TIM_clock);
#endif


	//�㉺�̐ݒ�\�Ȏ��g���̒��ɔ[�܂��Ă��邩�m�F
	if(frequency<FREQUENCY_UNDER_LIMIT || frequency>TIM_clock/PRESCALER_UNDER_LIMIT/PERIOD_UNDER_LIMIT)
	{
#ifdef PRINTF_AVAILABLE
		printf("Error. Frequency value out of range. '%d' - '%d' Requested frequency '%d'\n",FREQUENCY_UNDER_LIMIT,TIM_clock/PRESCALER_UNDER_LIMIT/PERIOD_UNDER_LIMIT,frequency);
#endif
		return 1;													//����������΃G���[�Ԃ��ďI��
	}

	//prescaler,period���v�Z
	while(calc_retry_flag)											//period���������̍ő�ɂȂ�܂�prescaler���グ�Ă��邾���B�v�Z�ł��o���邯�ǁA�����ڂ����͂������̂ق������ꂢ�B
	{
		prescaler++;
		period=TIM_clock/prescaler/frequency;
		if(period<=PERIOD_LIMIT) calc_retry_flag=0;
		if(prescaler>=PRESCALER_LIMIT){								//prescaler����̐����𒴂����������G���[�𗚂����ǂ����͂Ȃ�Ȃ��B
#ifdef PRINTF_AVAILABLE
			printf("Error. Prescaler value out of range. '%d'-'%d' \n",PRESCALER_UNDER_LIMIT,PRESCALER_LIMIT);
#endif
			return 1;												//����������΃G���[�Ԃ��ďI��
		}
	}
//	error_ratio=fabs(((float)TIM_clock/prescaler/period-(float)frequency)/(float)frequency)*100;//���g���̌덷���p�[�Z���g�Ōv�Z�B1%�ȓ��ɂ͔[�܂�B
	frequency=TIM_clock/prescaler/period;							//�ݒ肵�����l����Z�o�������g���@��̓����B
#ifdef PRINTF_AVAILABLE
	printf("Result: \n period:%d,\n prescaler:%d,\n frequency:%d,\n\n",period,prescaler,frequency);
#endif


	//�������畁�ʂ�PWM�ݒ�
	//�ݒ�Ɏg�p����\���̂̐錾
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;					//TIM�ݒ�p�\���̐錾
	TIM_OCInitTypeDef TIM_OCInitStructure;							//OC�ݒ�p�\���̐錾
	TIM_BDTRInitTypeDef 		TIM_BDTRInitStructure;

	//�N���b�N����
	RCC_PeriphClock_TIM(TIMx);//TIM�N���b�N����
	//�N���b�N������GPIO�ݒ�
	Init_port(GPIO_Mode_AF,GPIOx,pin,GPIO_PuPd_NOPULL,GPIO_OType_PP);

	//TIM�ݒ�
	TIM_TimeBaseStructure.TIM_Period = period-1;					//�v�Z����period-1
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler-1;				//�v�Z����prescaler-1
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			//�Ȃ񂩂����ς��Ă����g���ς��Ȃ������񂾂�ˁ@�i�j�R��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//�J�E���^�[���[�h�A�b�v�ݒ�
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;				//���@�\�^�C�}�[�p�@��{0
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseStructure);	//�ݒ菑������

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				//PWM���[�h1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		//�A�N�e�B�u���x�����̋ɐ���High���x���ɃZ�b�g
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;		//�A�N�e�B�u���x�����̋ɐ���High���x���ɃZ�b�g
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//�^�C�}�o�͂�L����
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;	//�^�C�}�o�͂�L����
	TIM_OCInitStructure.TIM_OCIdleState= TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState= TIM_OCNIdleState_Set;

	TIM_OC1Init(TIMx,&TIM_OCInitStructure);							//������
	TIM_OC1PreloadConfig(TIMx,TIM_OCPreload_Disable);				//�v�����[�h�s����
	TIM_OC2Init(TIMx,&TIM_OCInitStructure);							//������
	TIM_OC2PreloadConfig(TIMx,TIM_OCPreload_Disable);				//�v�����[�h�s����
	TIM_OC3Init(TIMx,&TIM_OCInitStructure);							//������
	TIM_OC3PreloadConfig(TIMx,TIM_OCPreload_Disable);				//�v�����[�h�s����
	TIM_OC4Init(TIMx,&TIM_OCInitStructure);							//������
	TIM_OC4PreloadConfig(TIMx,TIM_OCPreload_Disable);				//�v�����[�h�s����

	/*TIM1��TIM8��STM32�̒��ł����@�\�^�C�}�ɕ��ނ���A
	���[�^����p�Ɏg�p�����BREAK���͋@�\�����Ă���
	����BREAK�@�\�̒���output�̗L�����Ƃ����@�\������A�f�t�H���g�̐ݒ��
	�^�C�}�[�o�͂��Ƃ�output�������ɐݒ肳��Ă��邽��PWM�M�����~�܂�B
	���̂��߁A �^�C�}�̍X�V�C�x���g���Ƃ�output�������I�ɍėL���ɂȂ�悤�ɐݒ肷��B*/
	if(TIMx == TIM1||TIMx == TIM8){
		TIM_BDTRStructInit(&TIM_BDTRInitStructure);
		TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
		TIM_BDTRConfig(TIMx, &TIM_BDTRInitStructure);
		TIM_CtrlPWMOutputs(TIMx, ENABLE);
	}
	Analysis_GPIO_Pin(pin, &pin_state);

	for (i = 0; i < 16; i++){
		if (pin_state.user_pin[i] == 1){
			GPIO_PinAFConfig(GPIOx, Pin_select_source(pin_state.pin_address[i]), Tim_select_af(TIMx));//AF�ݒ�
		}
	}

	TIMx->CCR1=0;TIMx->CCR2=0;TIMx->CCR3=0;TIMx->CCR4=0;			//�ꉞduty�S��0%�ɂ��Ă���

	TIM_ARRPreloadConfig(TIMx,ENABLE);//�v�����[�h�ݒ�̓K�p
	TIM_Cmd(TIMx,ENABLE);//�^�C�}�[�L����

	return 0;
}


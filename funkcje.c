#include "funkcje.h"

//---------------BLUETOOTH-----------------------------//
void UART_GPIOC_init(uint32_t baudRate)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	//Rx & Tx
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//Tx Rx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);


	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


	USART_Init(USART3, &USART_InitStructure);


	USART_Cmd(USART3, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	NVIC_EnableIRQ(USART3_IRQn);
}

//-----------------------SPEAKER------------------------------------------------//
//Speaker

void SpeakerInit(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);


	GPIO_InitTypeDef  GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure2);


	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);

	ADC_Cmd(ADC1, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef port;

	port.GPIO_Pin = GPIO_Pin_4;
	port.GPIO_Mode = GPIO_Mode_AN;
	port.GPIO_OType = GPIO_OType_PP;
	port.GPIO_Speed = GPIO_Speed_100MHz;
	port.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &port);


	DAC_InitTypeDef DAC_InitStructure;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_SetChannel1Data(DAC_Align_12b_R, 0x0000);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 250-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 10-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

}

//---------------------------------ENGINE-----------------------------------------------------//

void stopEngine(){
	GPIO_ResetBits(GPIOE,GPIO_Pin_1|GPIO_Pin_2| GPIO_Pin_3|GPIO_Pin_4 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);

}
void moveForward(){
	GPIO_SetBits(GPIOE,GPIO_Pin_1|GPIO_Pin_4 | GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_7);
}
void moveBackward(){
	GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3 | GPIO_Pin_7 | GPIO_Pin_8);
	GPIO_ResetBits(GPIOE,GPIO_Pin_1|GPIO_Pin_4 | GPIO_Pin_9 | GPIO_Pin_10);
}
void moveLeft(){
	GPIO_SetBits(GPIOE,GPIO_Pin_1 | GPIO_Pin_9 | GPIO_Pin_2 );
	//GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3 |GPIO_Pin_4);
}
void moveRight(){
	GPIO_SetBits(GPIOE,GPIO_Pin_4 | GPIO_Pin_10 | GPIO_Pin_3  );
	//GPIO_ResetBits(GPIOE,GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1);
}

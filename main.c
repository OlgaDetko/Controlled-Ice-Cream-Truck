
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_dac.h"
#include "stm32f4_discovery.h"
#include "funkcje.h"


extern const u8 rawData[476173];//dzwiek
char cmd[2];//bluetooth/uart commands
int index=0;
uint16_t timer2cnt=0;

char X=0;//forward/backward value from bluetooth
char Y=0;//left/right value from bluetooth
char direction=0;//0-forward, 1-backward, 2-left, 3-right

//speaker values
u8 dac;
int array_index;
int volume=1;
char soundEnabled=0;
char sound=1;


//------------------SOUND-------------------------------//

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{

		switch(sound)
		{
		case 1:
		{
			dac=rawData[array_index]*1.3;
			DAC_SetChannel1Data(DAC_Align_12b_R,dac);
			array_index++;
			if(array_index==476173)  /*54068*/
			{
				array_index=0;
				TIM2->CNT=0;
				TIM_Cmd(TIM2,DISABLE);
			}
			break;
		}
		default:
		{
			break;
		}
		}


		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}


//BluetoothControl
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{

		cmd[index]=USART_ReceiveData(USART3);
		if(++index>2)
			index=0;

		switch(cmd[0])
		{
		case '0':
		{
			direction=0;
			index=0;
			break;
		}
		case '1':
		{
			direction=1;
			index=0;
			break;
		}
		case '2':
		{
			direction=2;
			index=0;
			break;
		}
		case '3':
		{
			direction=3;
			index=0;
			break;
		}
		case '4':
		{
			direction=4;
			index=0;
			break;
		}
		case '5':
		{

			TIM2->CNT=0;
			TIM_Cmd(TIM2,ENABLE);
			sound=1;
			array_index=0;
			index=0;
			break;
		}
		default:
		{
			index=0;
			break;
		}
		}

	}
}



void BluetoothControl()
{
	switch(direction){

	case 0:
	{
		stopEngine();
		break;
	}
	case 1:
	{
		moveForward();
		break;
	}
	case 2:
	{
		moveLeft();
		break;
	}
	case 3:
	{
		moveRight();
		break;
	}
	case 4:
	{
		moveBackward();
		break;
	}

	}

}


int main(void)
{

	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	//speaker
	SpeakerInit();

	//diody
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure3;

	GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14  ;
	GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure3.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure3.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure3);

	UART_GPIOC_init(9600);
	for(;;){

		timer2cnt=TIM2->CNT;

		GPIO_SetBits(GPIOD, GPIO_Pin_12 |GPIO_Pin_13);

		BluetoothControl();

	}
}

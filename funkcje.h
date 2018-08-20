#ifndef config_h
#define config_h
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

void UART_GPIOC_init(uint32_t baudRate);

void SpeakerInit();

void stopEngine();
void moveForward();
void moveBackward();
void moveLeft();
void moveRight();


#endif

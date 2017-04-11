#include "timer.h"


void timer2_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	uint16_t TimerPeriod; // 16-bit value because ARR register is 16-bit (although TIM2 is 32-bit!)
	RCC_ClocksTypeDef RCC_Clocks; // for reading current clock setting - useful
	uint32_t APB1_CLK; // APB1 clock - max. 36 MHz! 
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
	
	RCC_GetClocksFreq(&RCC_Clocks); // fill query struct
	APB1_CLK = RCC_Clocks.PCLK1_Frequency;
	TimerPeriod = (uint16_t)(((APB1_CLK * 2)/ 1000 ) - 1); //timer freq=APB1_CLK*2  1000khz
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;          
  TIM_TimeBaseStructure.TIM_Prescaler = 0;       
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	
	// set TIM2 IRQ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	// Enable the TIM2 global Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// TIM2 counter enable
 TIM_Cmd(TIM2, ENABLE);



}

#include "main.h"

 uint8_t timer_flag = 0;

void TIM2_IRQHandler(void)
{
if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
	timer_flag++;
	}
}



int main(void)
{
	gpio_Config_LED();
	gpio_Config_MCO();
	
	
	
	
	GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_SET);
	while(1)
	{
		if (timer_flag%2 == 0)
		{
			GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_SET);
		}
		else
		{
			timer_flag=0;
			GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_RESET);
		}
	}
}	

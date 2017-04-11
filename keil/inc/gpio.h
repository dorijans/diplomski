#ifndef GPIO_H
#define GPIO_H

#include <stm32f30x.h>
#include <stm32f30x_gpio.h> 
#include <stm32f30x_rcc.h> 

void gpio_Config_LED(void);
void gpio_Config_MCO(void);

#endif

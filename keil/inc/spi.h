#ifndef SPI_H
#define SPI_H


#include <stm32f30x.h>
#include <stm32f30x_spi.h>
#include <stm32f30x_gpio.h> 
#include <stm32f30x_rcc.h> 

#define SPI2_SCK_GPIO_PIN 		GPIO_Pin_13
#define SPI2_MOSI_GPIO_PIN		GPIO_Pin_15
#define SPI2_NSS_DDS					GPIO_Pin_1
#define SPI2_NSS_DAC					GPIO_Pin_2


void SPI2_init(void);
void SPI2_send(uint16_t data, uint16_t slave);
#endif

#include "spi.h"


void SPI2_init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStruct;
	SPI_InitTypeDef 	SPI_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE);
	
	GPIO_PinAFConfig(GPIOB, SPI2_SCK_GPIO_PIN,GPIO_AF_6 );
	GPIO_PinAFConfig(GPIOB, SPI2_MOSI_GPIO_PIN,GPIO_AF_6 );
	
	GPIO_InitStruct.GPIO_Pin = SPI2_SCK_GPIO_PIN | SPI2_MOSI_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	// set NSS bits
	GPIO_InitStruct.GPIO_Pin = SPI2_NSS_DDS | SPI2_NSS_DAC;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_SetBits(GPIOB, SPI2_NSS_DDS);
	GPIO_SetBits(GPIOB, SPI2_NSS_DAC);
	
	
	
	SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx; 
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;     
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b; 
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;        
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;      
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft; 
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; 
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStruct); 
	
	SPI_Cmd(SPI2, ENABLE);
	
}


void SPI2_send(uint16_t data, uint16_t slave)
{
	GPIO_ResetBits(GPIOB,slave); // nss low
	SPI_I2S_SendData16(SPI2,data);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY));
	GPIO_SetBits(GPIOB, slave); // nss high
}

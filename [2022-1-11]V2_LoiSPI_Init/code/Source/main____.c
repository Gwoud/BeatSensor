
/*******************************************************************************
 * Include
 ******************************************************************************/
#include <stm32f10x.h>
#include "TIMER.h"
#include "SPI.h"
//#include "LoRa.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void IO_Init (void);
static void SensorSW(void);
//static void SendID (void);
void EXTI3_IRQHandler(void);
void delay (void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
//static BitAction t = Bit_SET;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
 
static void IO_Init (void){
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
	
	/* config port c - pin 13 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	/*enable clk*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	
	/* config port a - pin 0  : SS1 control */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* config port a - pin 1 : ss2 control */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* config port a - pin 2 : ss3 control*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/* config port a - pin 3 : in put (send data)*/
	GPIO_InitStruct.GPIO_Mode = /* GPIO_Mode_AIN; */ GPIO_Mode_IPD; /* GPIO_Mode_IN_FLOATING; */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOA,&GPIO_InitStruct);
	
	/* Enable clock for AFIOEN*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	/* 0001: PB[x] pin */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
	/* Clear the the EXTI line interrupt pending bit */
	EXTI_ClearITPendingBit(EXTI_Line3);
	/*EXTI line Configuration */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  /* EXTI_Trigger_Falling; */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/*NVIC Configuration*/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
static void SensorSW() {
    if (TIMER_GetSensor() == Sensor1){
        GPIO_WriteBit (GPIOA, GPIO_Pin_0, 1);
        GPIO_WriteBit (GPIOA, GPIO_Pin_1, 0);
        GPIO_WriteBit (GPIOA, GPIO_Pin_2, 0);
    }

    if (TIMER_GetSensor() == Sensor2){
        GPIO_WriteBit (GPIOA, GPIO_Pin_0, 0);
        GPIO_WriteBit (GPIOA, GPIO_Pin_1, 1);
        GPIO_WriteBit (GPIOA, GPIO_Pin_2, 0);
    }
    
    if (TIMER_GetSensor() == Sensor3){
        GPIO_WriteBit (GPIOA, GPIO_Pin_0, 0);
        GPIO_WriteBit (GPIOA, GPIO_Pin_1, 0);
        GPIO_WriteBit (GPIOA, GPIO_Pin_2, 1);
    }
    TIMER_ResetStatus ();
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
 
int main (void) {
	//LoRa myLoRa;

	/* init IO pin */
	IO_Init();
	/* init Lora */
	// myLoRa = newLoRa();
	// LoRa_init (&myLoRa);
	// myLoRa.CS_port = 
	// myLoRa.
	/* init Timer */
	TIMER_SetPeriod (10000, 10000, 10000);
	TIMER_Init ();
	
/*========  finding is not easy  =================*/	
//	GPIO_ResetBits (GPIOC, GPIO_Pin_13);

//    SPI_InitTypeDef spi2Init;
//    GPIO_InitTypeDef gpioInit;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//    
//	
//	
//    /* PB12 - CS */
//	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
//	gpioInit.GPIO_Pin = GPIO_Pin_12;
//	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOB, &gpioInit);
//	
//	/* PB13 - SCK */
//	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
//	gpioInit.GPIO_Pin = GPIO_Pin_13;
//	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOB, &gpioInit);
//	
//	/* PB14 - MISO */
//	gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	gpioInit.GPIO_Pin = GPIO_Pin_14;
//	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOB, &gpioInit);
//	
//	/* PB15 - MOSI */
//	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
//	gpioInit.GPIO_Pin = GPIO_Pin_15;
//	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOB, &gpioInit);	
//	
//	/* SPI2 */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
//	spi2Init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
//	spi2Init.SPI_CPHA = SPI_CPHA_1Edge;
//	spi2Init.SPI_CPOL = SPI_CPOL_Low;
//	spi2Init.SPI_DataSize = SPI_DataSize_8b;
//	spi2Init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//	spi2Init.SPI_FirstBit = SPI_FirstBit_MSB;
//	spi2Init.SPI_Mode = SPI_Mode_Master;
//	spi2Init.SPI_NSS = SPI_NSS_Soft;
//	SPI_Init(SPI2, &spi2Init);
//	
//	SPI_I2S_ITConfig (SPI2, SPI_I2S_IT_RXNE, ENABLE);
//	
//	SPI_Cmd(SPI2, ENABLE);

/*===============================================*/
	
	
	SPI_Initialize ();
	
	/* demo nhap nhay */
	// int TempId = 1000;
    // while (1) {
	// 	GPIO_SetBits (GPIOC, GPIO_Pin_13);
	// 	while ( TempId > 0 )
	// 	{
	// 		TempId --;
	// 	}
	// 	TempId = 1000000;
	// 	GPIO_ResetBits (GPIOC, GPIO_Pin_13);
	// 	while ( TempId > 0 )
	// 	{
	// 		TempId --;
	// 	}
	// 	TempId = 1000000;
    // } 

	/* dung chuan phat xung */   
	    // while (1) {
        // if (TIMER_GetStatus() == Done) {			        
		// 	SensorSW();
		// }

	/* demo SPi */
	while (1) {
		GPIO_ResetBits (GPIOB, GPIO_Pin_12);
		SPI_I2S_SendData(SPI2, 'a');
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {}
		GPIO_SetBits (GPIOB, GPIO_Pin_12);
		delay ();
	}

}


/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
void EXTI3_IRQHandler(){
	// static uint8_t t = 0;
	// if (t == 0) 
	// {
	// 	GPIO_SetBits (GPIOC, GPIO_Pin_13);
	// }
	// else
	// GPIO_ResetBits (GPIOC, GPIO_Pin_13)
	GPIO_ResetBits (GPIOB, GPIO_Pin_12);
	SPI_I2S_SendData(SPI2, 'a');
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {}
	GPIO_SetBits (GPIOB, GPIO_Pin_12);
	EXTI_ClearITPendingBit(EXTI_Line3);
	//t = ~t;
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
void delay ()
{
	int i = 0;
	for (i =0; i < 10000000; i ++)
	{
		/*do nothing*/
	}
}

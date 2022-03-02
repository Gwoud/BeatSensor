/*******************************************************************************
 * Include
 ******************************************************************************/
#include "UART.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

void UART_Init (uint32_t Rate, uint16_t Parity, uint16_t StopBit){
	
//	GPIO_InitTypeDef gpioInit;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	
//	/* PB10 - TX */
//	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
//	gpioInit.GPIO_Pin = GPIO_Pin_10;
//	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOB, &gpioInit);
//	
//	/* PB11 - RX */
//	gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	gpioInit.GPIO_Pin = GPIO_Pin_11;
//	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;

//	GPIO_Init(GPIOB, &gpioInit);
//	
//	/* init uart */
//	USART_InitTypeDef USART_InitStruct;
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
//	
//	USART_InitStruct.USART_BaudRate = Rate ;
//	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_InitStruct.USART_Parity = Parity;
//	USART_InitStruct.USART_StopBits = StopBit;
//	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
//	USART_Init(USART3, &USART_InitStruct);
//	USART_Cmd (USART3, ENABLE);

	GPIO_InitTypeDef gpioInit;
	USART_InitTypeDef uartInit;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* PB10 TX */
	gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_10;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	/* PB11 RX */
	gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInit.GPIO_Pin = GPIO_Pin_11;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
	
	uartInit.USART_BaudRate = 9600;
	uartInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uartInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uartInit.USART_Parity = USART_Parity_No;
	uartInit.USART_StopBits = USART_StopBits_1;
	uartInit.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3, &uartInit);
	
	USART_Cmd(USART3, ENABLE);
}


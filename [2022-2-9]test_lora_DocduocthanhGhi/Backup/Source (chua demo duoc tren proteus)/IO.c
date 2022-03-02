/*******************************************************************************
 * Include
 ******************************************************************************/
#include "stm32f10x.h"
#include "IO.h"
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

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
 
void IO_Init (){
	GPIO_InitTypeDef GPIO_InitStruct;
	/* enable clk */
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA, ENABLE);
	/* */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOA, &GPIO_InitStruct);
}
 
 
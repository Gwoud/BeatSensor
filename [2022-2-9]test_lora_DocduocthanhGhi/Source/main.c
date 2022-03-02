
/*******************************************************************************
 * Include
 ******************************************************************************/
#include <stm32f10x.h>
#include "TIMER.h"
#include "SPI.h"
#include "IO.h"
#include "LORA.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
// static void IO_Init (void);
static void SensorSW(void);
//static void SendID (void);
void EXTI3_IRQHandler(void);
void delay (void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
//static BitAction t = Bit_SET;
static lora_pins_t lora_pins;             // Structure variable for lora pins
static lora_t lora;					     // Structure variable for lora


/*******************************************************************************
 * Code
 ******************************************************************************/


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
	// uint16_t a = 0;
	// //uint8_t* buf;

	lora_pins.nss.port   = GPIOB;				// NSS pin to which port is connected
	lora_pins.nss.pin    = GPIO_Pin_12;					// NSS pin to which pin is connected
	lora_pins.reset.port = GPIOA;			// RESET pin to which port is connected
	lora_pins.reset.pin  = GPIO_Pin_8;			// RESET pin to which pin is connected
	
	lora.pin = &lora_pins;											
	lora.frequency = FREQ_433MHZ;				 // 433MHZ Frequency 
	// lora.frequency = FREQ_865MHZ;				 // 865MHZ Frequency
	// lora.frequency = FREQ_866MHZ;				 // 866MHZ Frequency
	// lora.frequency = FREQ_867MHZ;				 // 867MHZ Frequency

	/* init IO pin */
	IO_Init();
	SPI_Initialize ();
	TIMER_SetPeriod (10000, 10000, 10000);
	TIMER_Init ();
	
	while (1)
	{
		LORA_init(&lora);
		TIMER_Delay_ms (100);
	}
	// //while(LORA_init(&lora)){}		         // Initialize the lora module
	

	// /* demo SPi */
	// while (1) {
	// 	GPIO_ResetBits (GPIOB, GPIO_Pin_12);
	// 	//SPIx->DR = 12;
	// 	SPI_I2S_SendData(SPI2, 'a');
	// 	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET) {}
	// 	GPIO_SetBits (GPIOB, GPIO_Pin_12);
	// 	TIMER_Delay_ms (10);
	// }
	IO_Init();
	TIMER_Init ();
	TIMER_SetPeriod (10, 10, 20000);
	
	SPI_Initialize ();
    while (1) {
        if (TIMER_GetStatus() == Done) {			        
			SensorSW();
		} 
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


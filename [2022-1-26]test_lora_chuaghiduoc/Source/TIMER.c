/*******************************************************************************
 * Include
 ******************************************************************************/
#include "TIMER.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PRESCALE 72U
#define RELOAD_VAR 1000U //max = 0xffff

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void TIM2_IRQHandler (void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static CntStatusType Status = Counting;
static SensorType Sensor = Sensor1;

static uint16_t g_u16S1Time;
static uint16_t g_u16S2Time;
static uint16_t g_u16S3Time;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*------------------------------------------------------------------------------
 * function name : TIMER_Init
 * fuction : config TIMER, enable interrupt*/
void TIMER_Init(void)
{	
	NVIC_InitTypeDef  NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TimerInit;
	
	/*enable clk*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TimerInit.TIM_CounterMode = TIM_CounterMode_Up;
	TimerInit.TIM_Period = RELOAD_VAR;
	TimerInit.TIM_Prescaler = PRESCALE - 1;
	TIM_TimeBaseInit(TIM2, &TimerInit);
	/* Enable TIM2 Update interrupts */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	/* clr timer interrupt flag*/
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	/* TIM2 enable counters */
	TIM_Cmd(TIM2, ENABLE);
 
    /* Configure two bits for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    /* Enable the TIM2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    

}
/*------------------------------------------------------------------------------
 * function name : TIMER_SetPeriod
 * fuction : Set sensor period (unit 1ms)*/
void TIMER_SetPeriod (uint16_t S1time, uint16_t S2time, uint16_t S3time) {
	g_u16S1Time = S1time;
	g_u16S2Time = S2time;
	g_u16S3Time = S3time;
}
/*------------------------------------------------------------------------------
 * function name : CntStatusType
 * fuction : return time for which sensor*/
CntStatusType TIMER_GetStatus () {
	return Status;
}

/*------------------------------------------------------------------------------
 * function name : CntStatusType
 * fuction : return time for which sensor*/
SensorType TIMER_GetSensor () {
	return Sensor;
}

/*------------------------------------------------------------------------------
 * function name : CntStatusType
 * fuction : return time for which sensor*/
void TIMER_ResetStatus () {
	Status = Counting;
}


/*------------------------------------------------------------------------------
 * function name : TIM2_IRQHandler
 * fuction : create sensor period*/
void TIM2_IRQHandler () {
	/* Clear TIM2 update interrupt */
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	static uint16_t cnt;
	cnt ++;
	switch (Sensor) {
		case Sensor1:
			if (cnt == g_u16S1Time){
				cnt = 0;
				Status = Done;
				Sensor = Sensor2;
			} 
			break;
		case Sensor2:
			if (cnt == g_u16S2Time) {
				cnt = 0;
				Status = Done;
				Sensor = Sensor3;
			}
			break;
		case Sensor3:
			if (cnt == g_u16S3Time){
				cnt = 0;
				Status = Done;
				Sensor = Sensor1;
			} 
			break;
	}		
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
void TIMER_Delay_ms (uint32_t Time)
{
	
	SysTick->LOAD = 72 * 1000 - 1; /* systerm clk = 72MHz */
	SysTick->VAL = 0;
	SysTick->CTRL = 5;             /* chon sys clk, enable systick */
	while (Time > 0)
	{
		while (!(SysTick->CTRL & (1 << 16))) {}
		Time --;
	}
}

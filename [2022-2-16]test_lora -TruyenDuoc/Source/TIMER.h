#ifndef _TIMER_H_
#define _TIMER_H_
/*******************************************************************************
 * Include
 ******************************************************************************/
#include "stm32f10x.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum {
    Done,
    Counting
}CntStatusType;

typedef enum {
    Sensor1,
    Sensor2,
	Sensor3
}SensorType;

/*******************************************************************************
 * API
 ******************************************************************************/

/* ==================================== */
void TIMER_Init(void);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
void TIMER_SetPeriod (uint16_t S1time, uint16_t S2time, uint16_t S3time);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
CntStatusType TIMER_GetStatus (void);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
SensorType TIMER_GetSensor (void);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
void TIMER_ResetStatus (void);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
void TIMER_Delay_ms (uint32_t Time);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

#endif /* _TIMER_H_ */

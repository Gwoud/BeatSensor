#ifndef _UART_H_
#define _UART_H_
/*******************************************************************************
 * Include
 ******************************************************************************/
#include "stm32f10x.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

void UART_Init (uint32_t Rate, uint16_t Parity, uint16_t StopBit);

#endif /* _UART_H_ */

/* This Driver is suitable for SX1276/7/8 Lora module
 * Author: Vinod Kumar from Vinod Embedded
 * Fix ver: Gwoud19 
 * lora driver
 */
 
#ifndef __LORA_H__
#define __LORA_H__
/*******************************************************************************
 * Include
 ******************************************************************************/
#include "stm32f10x.h"
#include <stdio.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* ==================================== */
#define REG_FIFO                 0x00
#define REG_OP_MODE              0x01
#define REG_FRF_MSB              0x06
#define REG_FRF_MID              0x07
#define REG_FRF_LSB              0x08
#define REG_PA_CONFIG            0x09
#define REG_LNA                  0x0c
#define REG_FIFO_ADDR_PTR        0x0d
#define REG_FIFO_TX_BASE_ADDR    0x0e
#define REG_FIFO_RX_BASE_ADDR    0x0f
#define REG_FIFO_RX_CURRENT_ADDR 0x10
#define REG_IRQ_FLAGS            0x12
#define REG_RX_NB_BYTES          0x13
#define REG_PKT_SNR_VALUE        0x19
#define REG_PKT_RSSI_VALUE       0x1a
#define REG_MODEM_CONFIG_1       0x1d
#define REG_MODEM_CONFIG_2       0x1e
#define REG_PREAMBLE_MSB         0x20
#define REG_PREAMBLE_LSB         0x21
#define REG_PAYLOAD_LENGTH       0x22
#define REG_MODEM_CONFIG_3       0x26
#define REG_RSSI_WIDEBAND        0x2c
#define REG_DETECTION_OPTIMIZE   0x31
#define REG_DETECTION_THRESHOLD  0x37
#define REG_SYNC_WORD            0x39
#define REG_DIO_MAPPING_1        0x40
#define REG_VERSION              0x42

/* ==================================== */
// modes
#define MODE_LONG_RANGE_MODE     0x80
#define MODE_SLEEP               0x00
#define MODE_STDBY               0x01
#define MODE_TX                  0x03
#define MODE_RX_CONTINUOUS       0x05
#define MODE_RX_SINGLE           0x06

/* ==================================== */
// PA config
#define PA_BOOST                 0x80

/* ==================================== */
// IRQ masks
#define IRQ_TX_DONE_MASK           0x08
#define IRQ_PAYLOAD_CRC_ERROR_MASK 0x20
#define IRQ_RX_DONE_MASK           0x40

#define MAX_PKT_LENGTH           255

#define LORA_SS_PIN    GPIO_PIN_12
#define LORA_RESET_PIN GPIO_PIN_8
//#define LORA_DIO0_PIN  GPIO_PIN_10

#define LORA_SS_PORT    GPIOB
#define LORA_RESET_PORT GPIOA
//#define LORA_DIO0_PORT  GPIOB

/* ==================================== */
typedef struct {
	uint16_t pin;
	void * port;
} lora_gpio_t;

/* ==================================== */
typedef struct {
	lora_gpio_t reset;
	lora_gpio_t dio0;
	lora_gpio_t nss;
	//void * spi;
} lora_pins_t;

/* ==================================== */
typedef struct {
	lora_pins_t * pin;
	uint8_t frequency;
} lora_t;

/* ==================================== */
#define FREQ_433MHZ			0
#define FREQ_865MHZ			1
#define FREQ_866MHZ			2
#define FREQ_867MHZ			3

static const uint64_t FREQUENCY[4] = { 433E6, 865E6, 866E6, 867E6}; 
/*******************************************************************************
 * API
 ******************************************************************************/
/* ==================================== */
uint8_t LORA_read_reg(lora_t * module, uint8_t addr);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
void LORA_write_reg(lora_t * module, uint8_t addr, uint8_t cmd);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
uint8_t LORA_init(lora_t * module);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
int LORA_prasePacket(lora_t * module);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
uint8_t LORA_available(lora_t * module);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
uint8_t LORA_read(lora_t * module);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
uint8_t LORA_begin_packet(lora_t * module);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
void LORA_tx(lora_t * module, uint8_t * buf, uint8_t size);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
uint8_t LORA_end_packet(lora_t * module);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

/* ==================================== */
void LORA_set_frequency(lora_t * module, uint64_t freq);
/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */

#endif /* __LORA_H__ */


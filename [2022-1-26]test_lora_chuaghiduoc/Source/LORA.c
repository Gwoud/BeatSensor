/* This Driver is suitable for SX1276/7/8 Lora module
 * Author: Vinod Kumar from Vinod Embedded
 * fix ver: Gwoud19
 * lora driver
 */

/*******************************************************************************
 * Include
 ******************************************************************************/
#include "LORA.h"
#include "TIMER.h"
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
static uint8_t packetIndex;

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
 * function name : LORA_read_reg 
 * fuction : read reg var */
uint8_t LORA_read_reg(lora_t * module, uint8_t addr) {
    uint8_t txByte = addr & 0x7f;
    uint8_t rxByte = 0x00;

    GPIO_ResetBits (GPIOB, GPIO_Pin_12);
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != SET)
    {
        /* do nothing */
    }
    SPI_I2S_SendData(SPI2, txByte);

    // while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) != SET)
    // {
    //     /* do nothing */
    // }
    // rxByte = (uint8_t)SPI_I2S_ReceiveData(SPI2);

    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != SET)
    {
        /* do nothing */
    }
    SPI_I2S_SendData(SPI2, 0xFE);
    //rxByte = (uint8_t)SPI_I2S_ReceiveData(SPI2);/* clear data register */
    
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) != SET)
    {
        /* do nothing */
    }
    rxByte = (uint8_t)SPI_I2S_ReceiveData(SPI2);
    GPIO_SetBits (GPIOB, GPIO_Pin_12);
    return rxByte;
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
void LORA_write_reg(lora_t * module, uint8_t addr, uint8_t cmd){
    uint8_t add = addr | 0x80;

    GPIO_ResetBits (GPIOB, GPIO_Pin_12);
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != SET)
    {
        /* do nothing */
    }
    SPI_I2S_SendData(SPI2, add);
    
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) != SET)
    {
        /* do nothing */
    }
    SPI_I2S_SendData(SPI2, cmd);
    
    GPIO_SetBits (GPIOB, GPIO_Pin_12);
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
uint8_t LORA_init(lora_t * module){
    uint8_t ret;

    GPIO_ResetBits (module->pin->reset.port, module->pin->reset.pin);
    TIMER_Delay_ms (10);
    GPIO_SetBits (module->pin->reset.port, module->pin->reset.pin);
    TIMER_Delay_ms (10);
    
    ret = LORA_read_reg(module, /* REG_OP_MODE */ REG_VERSION);
    if(ret != 0x12){
        return 1;
    }
    
    LORA_write_reg(module, REG_OP_MODE, (MODE_LONG_RANGE_MODE | MODE_SLEEP));
		LORA_write_reg(module, REG_OP_MODE, 0x12);
		ret = LORA_read_reg(module, /* REG_OP_MODE */ REG_OP_MODE);
    //lora_write_reg(module, REG_FRF_MSB, 0x6C);
    //lora_write_reg(module, REG_FRF_MID, 0x40);
    //lora_write_reg(module, REG_FRF_LSB, 0x00);
    LORA_set_frequency(module, FREQUENCY[module->frequency]);
    LORA_write_reg(module, REG_FIFO_TX_BASE_ADDR, 0);
    LORA_write_reg(module, REG_FIFO_RX_BASE_ADDR, 0);
    ret = LORA_read_reg(module, REG_LNA);
    LORA_write_reg(module, REG_LNA, ret | 0x03);
    LORA_write_reg(module, REG_MODEM_CONFIG_3, 0x04);
    LORA_write_reg(module, REG_PA_CONFIG, 0x8f);
    LORA_write_reg(module, REG_OP_MODE, (MODE_LONG_RANGE_MODE | MODE_STDBY));
    return 0;
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
int LORA_prasePacket(lora_t * module){
    uint8_t packetLength = 0, irqFlags; //,ret;
    irqFlags = LORA_read_reg(module, REG_IRQ_FLAGS);
    //ret = LORA_read_reg(module, REG_MODEM_CONFIG_1);
    LORA_write_reg(module, REG_MODEM_CONFIG_1, 0x72);
    
    LORA_write_reg(module, REG_IRQ_FLAGS, irqFlags);

    if((irqFlags & IRQ_RX_DONE_MASK) && ((irqFlags & IRQ_PAYLOAD_CRC_ERROR_MASK) == 0)) {
        packetLength = LORA_read_reg(module, REG_RX_NB_BYTES);
        LORA_write_reg(module, REG_FIFO_ADDR_PTR, LORA_read_reg(module, REG_FIFO_RX_CURRENT_ADDR));
        LORA_write_reg(module, REG_OP_MODE, 0x81);
        packetIndex = 0;
    }
    else if((LORA_read_reg(module, REG_OP_MODE)) != (MODE_LONG_RANGE_MODE | MODE_RX_SINGLE)){
        LORA_write_reg(module, REG_FIFO_ADDR_PTR, 0);
        LORA_write_reg(module, REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_RX_SINGLE);
    }
    if((irqFlags & IRQ_PAYLOAD_CRC_ERROR_MASK)== IRQ_PAYLOAD_CRC_ERROR_MASK){
        return -1;
    }
    return packetLength;
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
uint8_t LORA_available(lora_t * module){
    return (LORA_read_reg(module, REG_RX_NB_BYTES) - packetIndex);
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
uint8_t LORA_read(lora_t * module){
    if(!LORA_available(module))
        return 0;
    packetIndex++;
    return LORA_read_reg(module, REG_FIFO);
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
uint8_t LORA_begin_packet(lora_t * module){
    //int ret;
    if ((LORA_read_reg(module, REG_OP_MODE) & MODE_TX) == MODE_TX) {
        return 1;
      }
    LORA_write_reg(module, REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_STDBY);
    LORA_write_reg(module, REG_MODEM_CONFIG_1, 0x72);
    LORA_write_reg(module, REG_FIFO_ADDR_PTR, 0);
      LORA_write_reg(module, REG_PAYLOAD_LENGTH, 0);
    return 0;
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
void LORA_tx(lora_t * module, uint8_t * buf, uint8_t size){
    uint8_t currentLength = LORA_read_reg(module, REG_PAYLOAD_LENGTH);
      if ((currentLength + size > MAX_PKT_LENGTH)){
        size = MAX_PKT_LENGTH - currentLength;
      }

      for (int i = 0; i < size; i++) {
        LORA_write_reg(module, REG_FIFO, buf[i]);
      }
      LORA_write_reg(module, REG_PAYLOAD_LENGTH, currentLength + size);
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
uint8_t LORA_end_packet(lora_t * module){
    uint8_t timeout = 100;
    LORA_write_reg(module, REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_TX);
      while((LORA_read_reg(module,REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK) == 0) {
        if(--timeout==0){
            TIMER_Delay_ms (1);
            return 1;
        }
      }
      LORA_write_reg(module, REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);
    return 0;
}

/*------------------------------------------------------------------------------
 * function name : 
 * fuction :  */
void LORA_set_frequency(lora_t * module, uint64_t freq){
    uint64_t frf = ((uint64_t)freq << 19) / 32000000;
      LORA_write_reg(module, REG_FRF_MSB, (uint8_t)(frf >> 16));
      LORA_write_reg(module,REG_FRF_MID, (uint8_t)(frf >> 8));
      LORA_write_reg(module,REG_FRF_LSB, (uint8_t)(frf >> 0));
}


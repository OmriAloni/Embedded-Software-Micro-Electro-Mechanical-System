
///////////////////////I2C1

#define I2C1_DisableAck()       I2C1_C1 |= I2C_C1_TXAK_MASK
#define I2C1_EnableAck()        I2C1_C1 &= ~I2C_C1_TXAK_MASK
#define I2C1_RepeatedStart()    I2C1_C1 |= I2C_C1_RSTA_MASK
#define I2C1_EnterRxMode()      I2C1_C1 &= ~I2C_C1_TX_MASK
#define I2C1_write_byte(data)   I2C1_D = data

#define I2C1_Start()            I2C1_C1 |= I2C_C1_TX_MASK;\
                               I2C1_C1 |= I2C_C1_MST_MASK

#define I2C1_Stop()             I2C1_C1 &= ~I2C_C1_MST_MASK;\
                               I2C1_C1 &= ~I2C_C1_TX_MASK

#define I2C1_Wait()             while((I2C1_S & I2C_S_IICIF_MASK)==0) {} \
                                I2C1_S |= I2C_S_IICIF_MASK;
void delay(int number);
void writeByte(uint8_t, uint8_t, uint8_t);
uint8_t readByte(uint8_t, uint8_t);
void readBytes(uint8_t, uint8_t, uint8_t, uint8_t *);
void MCU_Init1();

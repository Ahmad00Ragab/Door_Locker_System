/*===========================================================================================
 * Filename   : twi.h
 * Author     : Ahmad Haroun
 * Description: Header file for TWI Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/
#include "gpio.h"

#ifndef TWI_H_
#define TWI_H_





/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef unsigned char TWI_Address;

typedef unsigned long TWI_BaudRate;

typedef struct
{
	TWI_Address  address;
	TWI_BaudRate bit_rate;
}TWI_ConfigType;


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


 /**************************************************************************
 * Function Name: TWI_init
 * Description  : (Initialize TWI Module)
 * INPUTS       : Config_Ptr (Configuration of the TWI Module as a pointer to structure )
 * RETURNS      : void
 **************************************************************************/
void TWI_init(const TWI_ConfigType * Config_Ptr);


 /**************************************************************************
 * Function Name: TWI_start
 * Description  : (send start condition)
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TWI_start(void);


 /**************************************************************************
 * Function Name: TWI_stop
 * Description  : send the stop condition
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TWI_stop(void);


 /**************************************************************************
 * Function Name: TWI_writeByte
 * Description  : Write Data in TWDR to be Sent
 * INPUTS       : void
 * RETURNS      : uint8 (data to be sent)
 **************************************************************************/
void TWI_writeByte(uint8 data);


 /**************************************************************************
 * Function Name: TWI_readByteWithACK
 * Description  : Read the Received byte with positive ack
 * INPUTS       : void
 * RETURNS      : uint8 (data received)
 **************************************************************************/
uint8 TWI_readByteWithACK(void);


 /**************************************************************************
 * Function Name: TWI_readByteWithNACK
 * Description  : Read the Received byte with negative ack
 * INPUTS       : void
 * RETURNS      : uint8 (data received)
 **************************************************************************/
uint8 TWI_readByteWithNACK(void);


 /**************************************************************************
 * Function Name: TWI_getStatus
 * Description  : get the status of the transmission
 * INPUTS       : void
 * RETURNS      : uint8 (status)
 **************************************************************************/
uint8 TWI_getStatus(void);



#endif /* TWI_H_ */

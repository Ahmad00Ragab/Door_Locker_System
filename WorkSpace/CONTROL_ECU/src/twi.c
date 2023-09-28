/*===========================================================================================
 * Filename   : twi.c
 * Author     : Ahmad Haroun
 * Description: Source file for TWI Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/
#include "twi.h"


/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

 
/**************************************************************************
 * Function Name: TWI_init
 * Description  : (Initialize TWI Module)
 * INPUTS       : Config_Ptr (Configuration of the TWI Module as a pointer to structure )
 * RETURNS      : void
 **************************************************************************/


void TWI_init(const TWI_ConfigType * Config_Ptr)
{
	uint8 TWBR_Value;

	TWBR_Value = (uint8)( (uint32)(F_CPU - (16 * Config_Ptr->bit_rate) ) / (2 * Config_Ptr ->bit_rate) );

	TWBR = TWBR_Value;                          /*bit rate is 400 Kbps with F_CPU = 8Mhz */

	TWSR = 0x00;                                /* Prescaler =  0 */

	TWAR =  ((Config_Ptr->address) << 1);       /* disable General Call
	                                               put the address of this SPI Device in this register
	                                               to be used when any master wants to speak to me when i am a slave */
	TWCR  = (1<<TWEN);
}



 /**************************************************************************
 * Function Name: TWI_start
 * Description  : (send start condition)
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TWI_start(void)
{
	/*
	 * clear the TWINT flag
	 * send start condition
	 * enable the module
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* wait until the start condition is sent */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}


 /**************************************************************************
 * Function Name: TWI_stop
 * Description  : send the stop condition
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TWI_stop(void)
{
	/*
	 * clear the interrupt flag
	 * send the stop condition
	 * enable the module
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); /* you don't need to wait for the flag to be set */

}


 /**************************************************************************
 * Function Name: TWI_writeByte
 * Description  : Write Data in TWDR to be Sent
 * INPUTS       : void
 * RETURNS      : uint8 (data to be sent)
 **************************************************************************/
void TWI_writeByte(uint8 data)
{
	/* put the data inside the buffer */
	TWDR = data;
	/* clear the interrupt flag and enable the module */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* wait until the operation is completed */
	while(BIT_IS_CLEAR(TWCR,TWINT));

}

 /**************************************************************************
 * Function Name: TWI_readByteWithACK
 * Description  : Read the Received byte with positive ack
 * INPUTS       : void
 * RETURNS      : uint8 (data received)
 **************************************************************************/
uint8 TWI_readByteWithACK(void)
{

	/* enable the module
	 * clear the interrupt flag by writing one on it
	 * enable the Acknowledgement
	 */
	TWCR = (1 << TWINT) | (1 << TWEN)| (1 << TWEA) ;
	/* wait until the action is done */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

 /**************************************************************************
 * Function Name: TWI_readByteWithNACK
 * Description  : Read the Received byte with negative ack
 * INPUTS       : void
 * RETURNS      : uint8 (data received)
 **************************************************************************/
uint8 TWI_readByteWithNACK(void)
{
	/* enable the module
	 * clear the interrupt flag by writing one on it
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* wait until the action is done */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;

}


 /**************************************************************************
 * Function Name: TWI_getStatus
 * Description  : get the status of the transmission
 * INPUTS       : void
 * RETURNS      : uint8 (status)
 **************************************************************************/
uint8 TWI_getStatus(void)
{
	uint8 staus;
	staus = TWSR & 0xF8;
	return staus;
}

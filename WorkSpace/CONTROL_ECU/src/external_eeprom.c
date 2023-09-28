/*===========================================================================================
 * Filename   : external_eprom.c
 * Author     : Ahmad Haroun
 * Description: Source File for a 2KB EXTERNAL_EEPROM DRIVER
 * Created on : SEP 4, 2023
 *==========================================================================================*/
#include "external_eeprom.h"
#include "twi.h"


/*******************************************************************************
 *                              Functions Definitions                           *
 *******************************************************************************/


/**************************************************************************
 * Function Name: EEPROM_writeByte
 * Description  : Write a byte in a specific address
 * INPUTS       : uint16 address(address to write in), uint8 data(data to be written)
 * RETURNS      : uint8 (status of Writing Success or Fail)
 **************************************************************************/
uint8 EEPROM_writeByte(uint16 address, uint8 data)
{
	/* send the start condition and check for the Acknowledgement */
	TWI_start();
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR;
	}

 	/*  EEPROM used is 2KB so its address is 11-bits so we need to transmit the upper 3-bits first
 	 *  and after that we send the lower 8-bits
 	 *  ((uint8) ((0xA0) | ((address & 0x0700) >> 7))) ==> this formula extracts the A8, A9 and A10 bits
 	 *  from the address bits
 	 *  check for the Acknowledgement
 	 * */
	TWI_writeByte ((uint8) (0xA0 | ((address & 0x0700)>>7)));
	
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	{
		return ERROR;
	}

	/* Send the rest of the address that the master wants to write in the EEPROM
	 * check for the Acknowledgement
	 * */
	TWI_writeByte((uint8)address);

	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}

	/* Send the Data
	 * check for the Acknowledgement
	 * */
	TWI_writeByte(data);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}

	TWI_stop();
	
	return SUCCESS;

}



/**************************************************************************
 * Function Name: EEPROM_readByte
 * Description  : Read a byte from a specific address
 * INPUTS       : uint16 address(address to read from), uint8 *data(data to be read)
 * RETURNS      : uint8 (status of Writing Success or Fail)
 **************************************************************************/
uint8 EEPROM_readByte(uint16  address, uint8* data)
{
	/* send the start condition and check for the Acknowledgement */
	TWI_start();
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR;
	}
	/*  EEPROM used is 2KB so its address is 11-bits so we need to transmit the upper 3-bits first
	 *  and after that we send the lower 8-bits
	 *  ((uint8) ((0xA0) | ((address & 0x0700) >> 7))) ==> this formula extracts the A8, A9 and A10 bits
	 *  from the address bits
	 *  check for the Acknowledgement
	 * */
	 TWI_writeByte((uint8)((0xA0) | ((address & 0x0700)>>7)));
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
	{
		return ERROR;
	}

	/* Send the rest of the address that the master wants to write in the EEPROM
	 * check for the Acknowledgement
	 * */
	TWI_writeByte((uint8) address);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
	{
		return ERROR;
	}
	 /* Send the Repeated Start Bit */
	TWI_start();
	if(TWI_getStatus() != TWI_REP_START)
	{
		return ERROR;
	}

    TWI_writeByte((uint8)((0xA0) | ((address & 0x0700)>>7) | 1));
	 if(TWI_getStatus() != TWI_MT_SLA_R_ACK)
	{
		return ERROR;
	}

	*data = TWI_readByteWithNACK();
	if(TWI_getStatus() != TWI_MR_DATA_NACK)
	{
		return ERROR;
	}

	TWI_stop();

	return SUCCESS;

}

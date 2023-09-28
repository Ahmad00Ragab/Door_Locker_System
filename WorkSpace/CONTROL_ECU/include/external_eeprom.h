/*===========================================================================================
 * Filename   : external_eprom.h
 * Author     : Ahmad Haroun
 * Description: Header File for a 2KB EXTERNAL_EEPROM DRIVER
 * Created on : SEP 4, 2023
 *==========================================================================================*/

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_


#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SUCCESS  1
#define ERROR    0
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/



/**************************************************************************
 * Function Name: EEPROM_writeByte
 * Description  : Write a byte in a specific address
 * INPUTS       : uint16 address(address to write in), uint8 data(data to be written)
 * RETURNS      : uint8 (status of Writing Success or Fail)
 **************************************************************************/
uint8 EEPROM_writeByte(uint16 address, uint8 data);



/**************************************************************************
 * Function Name: EEPROM_readByte
 * Description  : Read a byte from a specific address
 * INPUTS       : uint16 address(address to read from), uint8 *data(data to be read)
 * RETURNS      : uint8 (status of Writing Success or Fail)
 **************************************************************************/
uint8 EEPROM_readByte(uint16  address, uint8* data);

#endif /* EXTERNAL_EEPROM_H_ */

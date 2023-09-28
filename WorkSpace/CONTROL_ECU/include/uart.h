/*===========================================================================================
 * Filename   : uart.h
 * Author     : Ahmad Haroun
 * Description: Header file UART Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/
#ifndef UART_H_
#define UART_H_

#include "gpio.h"



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef unsigned long UART_BaudRate;

typedef enum
{
	Character_5_bit,
	Character_6_bit,
	Character_7_bit,
	Character_8_bit,
}UART_BitData;

typedef enum
{
	Parity_Disabled,
	Reserved,
	Parity_Even_Parity,
	Parity_Odd_Parity,
}UART_Parity;

typedef enum
{
	Stop_One_bit,
	Stop_Two_bit,
}UART_StopBit;

typedef struct
{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**************************************************************************
 * Function Name: UART_init
 * Description  : (Initialize Uart Module)
 * INPUTS       : Config_Ptr (Configuration of the UART Module as a pointer to structure )
 * RETURNS      : void
 **************************************************************************/
void UART_init(const UART_ConfigType* Config_Ptr);



/**************************************************************************
 * Function Name: UART_sendByte
 * Description  : a function to transmit a character size to  another UART Device 
 * INPUTS       : uint8 (data to be sent)
 * RETURNS      : void
 **************************************************************************/
void UART_sendByte(uint8 data);



/**************************************************************************
 * Function Name: UART_receiveByte
 * Description  : a function to receive a character size from the another UART Device
 * INPUTS       : void
 * RETURNS      : uint8 (data Received) 
 **************************************************************************/
uint8 UART_recieveByte(void);



/**************************************************************************
 * Function Name: UART_sendString
 * Description  : a function to send a string as whole packet not a character by character
 * INPUTS       : uint8* str (String to be sent)
 * RETURNS      : void
 **************************************************************************/
void UART_sendString(const uint8* str);


/**************************************************************************
 * Function Name: UART_receiveString
 * Description  : a function to receive a string from the another UART Device 
 * INPUTS       : uint8* str (buffer to save the received string in)
 * RETURNS      : void
 **************************************************************************/
void UART_receiveString(uint8* str);


/**********************************************************************************
 * Function Name: UART_setCallBack
 * Description  : A Function to set the callBack functions for UART Events
 * INPUTS       : ptr_2_fun,index(which indicates which ISR would be Executed)
 * RETURNS      : void
 **********************************************************************************/
void UART_setCallBack(void (*ptr_2_func)(void),uint8 index);

#endif /* UART_H_ */

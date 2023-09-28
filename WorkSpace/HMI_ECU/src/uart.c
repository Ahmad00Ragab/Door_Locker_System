/*===========================================================================================
 * Filename   : uart.c
 * Author     : Ahmad Haroun
 * Description: Source file UART Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/

#include "uart.h"

/*******************************************************************************
 *                               Global_Variables Declaration                             *
 *******************************************************************************/
 
 
/********************************************************************************
 * Global Array of 3 pointers to function
 * 1.static to use in this file and hold his value
 * 2.volatile to use in ISRs function and in the function 'TIMER1_Set_CallBack'
 * 3.Initial value with Null or use NULL_Ptr in standard_types
 * USART_TXC_vect     : INDEX 0
 * USART_RXC_vect     : INDEX 1
 * USART_UDRE_vect    : INDEX 2
 *********************************************************************************/
static volatile void (*UART_CallBack_Array[3])(void);


/*******************************************************************************
 *                              Functions Definitions                           *
 *******************************************************************************/



#if (0)
/*********** In case of Using Interrupt ***************/

/**************************************************************************
 * Function Name: ISR (INTERRUPT HANDLER FOR USART_TXC_vect)
 * Description  : Call the Function that is required to be Executed when 
                  USART_TXC_vect happens [Transmit Complete] 
 **************************************************************************/
ISR(USART_TXC_vect)
{
	(*UART_CallBack_Array[0])();
}


/**************************************************************************
 * Function Name: ISR (INTERRUPT HANDLER FOR USART_RXC_vect)
 * Description  : Call the Function that is required to be Executed when 
                  USART_RXC_vect happens [Receive Complete] 
 **************************************************************************/
ISR(USART_RXC_vect)
{
	(*UART_CallBack_Array[1])();
}


/**************************************************************************
 * Function Name: ISR (INTERRUPT HANDLER FOR USART_UDRE_vect)
 * Description  : Call the Function that is required to be Executed when 
                  USART_UDRE_vect happens [UDR is Empty ] 
 **************************************************************************/
ISR(USART_UDRE_vect)
{
	(*UART_CallBack_Array[2])();
}
/*********** In case of Using Interrupt ***************/

#endif

/**************************************************************************
 * Function Name: UART_init
 * Description  : (Initialize Uart Module)
 * INPUTS       : Config_Ptr (Configuration of the UART Module as a pointer to structure )
 * RETURNS      : void
 **************************************************************************/
void UART_init(const UART_ConfigType* Config_Ptr)
{
	uint16 UBRR_value = 0;

	UCSRA = (1 << U2X);             /*Double Speed Mode */

	UCSRB = (1<<RXEN) | (1<<TXEN); /* Enable the UART TX/RX */

	/*
	 * 8-bit character Data
	 * URSEL is one to enable us from writing on UCSRC
	 */
	UCSRC = (1<<URSEL) | (Config_Ptr->bit_data << 1 ) |(Config_Ptr->parity << 4) | (Config_Ptr->stop_bit << 3);

	/* Calculate the UBRR register value */
	UBRR_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate* 8UL))) - 1);

	/* second 8 bits of the ubrr_value are set in UBRRH Register */
	UBRRH =(uint8)(UBRR_value >> 8);

	/* first 8 bits of the ubrr_value are set in UBRRL Register */
	UBRRL =(uint8)UBRR_value;

}



/**************************************************************************
 * Function Name: UART_sendByte
 * Description  : a function to transmit a character size to  another UART Device 
 * INPUTS       : uint8 (data to be sent)
 * RETURNS      : void
 **************************************************************************/
void UART_sendByte(uint8 data)
{
	/* check if the UDR is Ready to write in or not */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = data;
}



/**************************************************************************
 * Function Name: UART_receiveByte
 * Description  : a function to receive a character size from the another UART Device
 * INPUTS       : void
 * RETURNS      : uint8 (data Received) 
 **************************************************************************/
uint8 UART_recieveByte(void)
{
	/* make sure the receive is complete */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	return 	UDR;
}


/**************************************************************************
 * Function Name: UART_sendString
 * Description  : a function to send a string as whole packet not a character by character
 * INPUTS       : uint8* str (String to be sent)
 * RETURNS      : void
 **************************************************************************/
void UART_sendString(const uint8* str)
{
	uint8 i = 0;
	while(*str != '\0')
	{
		UART_sendByte(str[i]);
		str++;
	}
	UART_sendByte(str[i]);
}



/**************************************************************************
 * Function Name: UART_receiveString
 * Description  : a function to receive a string from the another UART Device 
 * INPUTS       : uint8* str (buffer to save the received string in)
 * RETURNS      : void
 **************************************************************************/
void UART_receiveString(uint8* str)
{
	uint8 i = 0;
	str[i] = UART_recieveByte();
	while(str[i] != '\0')
	{
		i++;
		str[i] = UART_recieveByte();
	}
}



/**********************************************************************************
 * Function Name: UART_setCallBack
 * Description  : A Function to set the callBack functions for UART Events
 * INPUTS       : ptr_2_fun,index(which indicates which ISR would be Executed)
 * RETURNS      : void
 **********************************************************************************/
void UART_setCallBack(void (*ptr_2_func)(void),uint8 index)
{
	UART_CallBack_Array[index] = ptr_2_func;
}

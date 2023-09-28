/*===========================================================================================
 * Filename   : MC1_HMI_ECU.c
 * Author     : Ahmad Haroun
 * Description: HMI_ECU Source File For DOOR_LOCKER_SYSTEM
 * Created on : SEP 4, 2023
 *==========================================================================================*/

/*===========================================================================================
 * SUMMARY:
 * HMI_ECU is just responsible interaction with the user just take inputs through keypad
 * and display messages on the LCD
 *==========================================================================================*/

/*===========================================================================================
 * Specification
 * MicroController    : ATMega32
 * CPU Frequency      : 8Mhz
 *********************
 * Drivers           *
 *********************
 * Display            : LCD (LM016L 2*16)
 * TIMER1             : USE TIMER1
 * KEYPAD             : USE 4x4 Keypad
 * GPIO               : USE GPIO
 * UART               : USE UART
 *==========================================================================================*/
#include "app.h"


/*******************************************************************************
 *                               Main                                          *
 *******************************************************************************/
int main()
{
	APP_init();        /* Initialize the Application */

	while(1)
	{
		APP_start();   /* Run the Application */
	}
}

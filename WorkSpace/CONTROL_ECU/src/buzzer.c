/*===========================================================================================
 * Filename   : buzzer.c
 * Author     : Ahmad Haroun
 * Description: Source file BUZZER Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/

#include "buzzer.h"

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/**************************************************************************
 * Function Name: Buzzer_init
 * Description  : make the buzzer ready to work
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void Buzzer_init()
{
	GPIO_setupPinDirection(PORTC_ID, PIN5_ID, PIN_OUTPUT);

	GPIO_writePin(PORTC_ID, PIN5_ID, LOGIC_LOW);

}


/**************************************************************************
 * Function Name: Buzzer_on
 * Description  : Turn on the buzzer
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void Buzzer_on(void)
{
	GPIO_writePin(PORTC_ID, PIN5_ID,LOGIC_HIGH);
}


/**************************************************************************
 * Function Name: Buzzer_off
 * Description  : Turn off the buzzer
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void Buzzer_off(void)
{
	GPIO_writePin(PORTC_ID, PIN5_ID,LOGIC_LOW);
}

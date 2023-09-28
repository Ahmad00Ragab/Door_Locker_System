/*===========================================================================================
 * Filename   : buzzer.h
 * Author     : Ahmad Haroun
 * Description: Header file BUZZER Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "gpio.h"


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/**************************************************************************
 * Function Name: Buzzer_init
 * Description  : make the buzzer ready to work
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void Buzzer_init();


/**************************************************************************
 * Function Name: Buzzer_on
 * Description  : Turn on the buzzer
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void Buzzer_on(void);



/**************************************************************************
 * Function Name: Buzzer_off
 * Description  : Turn off the buzzer
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void Buzzer_off(void);

#endif /* BUZZER_H_ */

/*===========================================================================================
 * Filename   : app.h
 * Author     : Ahmad Haroun
 * Description: Header file for the application Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/

#ifndef APP_H_
#define APP_H_

#include "std_types.h"


/*******************************************************************************
 *                      Definitions                                            *
 *******************************************************************************/
#define  EEPROM_PASSWORD_LOCATION   0X0311



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/**************************************************************************
 * Function Name: setPassword
 * Description  : This function is responsible for setting and updating
 *                the password of the system
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void setPassword(void);


/**************************************************************************
 * Function Name: verifyPassword
 * Description  : The function is to check if the passed two passwords are identical
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void verifyPassword(void);


/**************************************************************************
 * Function Name: openGate
 * Description  : This function is responsible to open the door
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void openGate(void);


/**************************************************************************
 * Function Name: lockSystem
 * Description  : This function is responsible for locking the system
 *                In case of password entered is wrong for 3 times
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void lockSystem(void);


/**************************************************************************
 * Function Name: isPassMatched
 * Description  : This function is to compare user entered password && system password
 * INPUTS       : void
 * RETURNS      : uint8
 * 			      1 ==> Passwords match
 * 			      0 ==> Passwords do not match
 **************************************************************************/
uint8 isPassMatched(uint8 * pass1, uint8 * pass2, uint8 size);



/**************************************************************************
 * Function Name: TIMER1_callback_function
 * Description  : The required function to be executed when timer interrupt
 *                is fired, "increments ticks variable"
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TIMER1_callback_function(void);



/**************************************************************************
 * Function Name: TIMER1_delay_15sec
 * Description  : This function is to generate 15 seconds delay using timer1.
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TIMER1_delay_15sec(void);


/**************************************************************************
 * Function Name: TIMER1_delay_3sec
 * Description  : This function is to generate 3 seconds delay using timer1.
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TIMER1_delay_3sec(void);



/**************************************************************************
 * Function Name: APP_init
 * Description  : This function is responsible for initializing the peripherals used
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void APP_init(void);


/**************************************************************************
 * Function Name: APP_start
 * Description  : This function is responsible for Running the system as required
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void APP_start(void);

#endif /* APP_H_ */

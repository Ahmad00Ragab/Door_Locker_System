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
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/**************************************************************************
 * Function Name: setPassword
 * Description  : This function is responsible for setting and updating
 *                the password of the system
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void setPass(void);


/**************************************************************************
 * Function Name: checkPassword_trials
 * Description  : This function is responsible for prompting the user for correct passwords,
 * 		          within maximum 3 times.
 * INPUTS       : void
 * RETURNS      : uint8
 *                1 Password is correct.
 * 		   	      0 All trials are used without password being correct
 **************************************************************************/
uint8 checkPassword_trials(void);


/**************************************************************************
 * Function Name: openDoor
 * Description  : This function is responsible for executing the steps required to open the door
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void openDoor(void);


/**************************************************************************
 * Function Name: lockSystem
 * Description  : This function is responsible for locking the system
 *                In case of password entered is wrong for 3 times
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void lockSystem(void);



/**************************************************************************
 * Function Name: getPass
 * Description  : This function is responsible for storing the user entered password,
 * 		          and printing '*' on LCD instead of each entered character
 * INPUTS       : password array && Size of password passed by address
 * RETURNS      : void
 **************************************************************************/
void getPass(uint8 *passArr, uint8 *size);


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
 * Function Name: verifyPass_ControlECU
 * Description  : This function is to compare password entered by user to
 *                the saved password of the system
 * INPUTS       : void
 * RETURNS      : uint8
 *                '1' Password is correct.
 * 		   	      '0' Password is false.
 **************************************************************************/
uint8 verifyPass_ControlECU(void);


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
 * Description  : This function is to generate 1 seconds delay using timer1.
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TIMER1_delay_1sec(void);



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

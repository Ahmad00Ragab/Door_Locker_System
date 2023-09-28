/*===========================================================================================
 * Filename   : motor.c
 * Author     : Ahmad Haroun
 * Description: Source file MOTOR Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/
#include "timer0.h"
#include "motor.h"
#include "gpio.h"
#include "common_macros.h"


/**************************************************************************
 * Function Name: DcMotor_Init
 * Description  : Initialize DC MOTOR
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void DcMotor_Init(void)
{
	/* Configure motor control pins as outputs */
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);     /* PIN 1 TO CONTROL THE MOTOR */
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);     /* PIN 2 TO CONTROL THE MOTOR */
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);     /* FOR PWM SIGNAL */

	/* Stop the motor at the beginning */
	GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW);
	GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
}



/**************************************************************************
 * Function Name: DcMotor_Rotate
 * Description  : Rotate the DC MOTOR with the input Speed
 * INPUTS       : state && speed
 * RETURNS      : void
 **************************************************************************/
void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{

	switch (state)
	{

	case stop:
		GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
		break;
	case rotate_CW:
		GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_HIGH);
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
		break;
	case rotate_A_CW:
		GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_HIGH);
		break;
	}
	speed = ((speed / 100.0) * 255);
	TIMER0_Init_PWM_Mode(speed, TIMER0_NON_INVERTING, TIMER0_PRESCALER_8, TIMER0_DISABLE_INTERRUPT);                 // Set motor speed using PWM
}


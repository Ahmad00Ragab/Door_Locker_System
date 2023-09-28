/*========================================================================================
 * Filename   : motor.h
 * Author     : Ahmad Haroun
 * Description: Header file MOTOR Driver
 * Created on : SEP 4, 2023
 *========================================================================================*/
#include "std_types.h"

#ifndef MOTOR_H_
#define MOTOR_H_

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	stop,
	rotate_A_CW,
	rotate_CW,

}DcMotor_State;


/**************************************************************************
 * Function Name: DcMotor_Init
 * Description  : Initialize DC MOTOR
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void DcMotor_Init(void);


/**************************************************************************
 * Function Name: DcMotor_Rotate
 * Description  : Rotate the DC MOTOR with the input Speed
 * INPUTS       : state && speed
 * RETURNS      : void
 **************************************************************************/
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* MOTOR_H_ */

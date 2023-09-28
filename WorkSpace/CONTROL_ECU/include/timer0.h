/*===========================================================================================
 * Filename   : timer0.h
 * Author     : Ahmad Haroun
 * Description: Header file ATMEGA32 Timer0 Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/
#ifndef TIMER0_H_
#define TIMER0_H_

#include "gpio.h"
#include <avr/interrupt.h>


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	TIMER0_NORMAL_PORT,
	TIMER0_TOGGLE_OC1A,
	TIMER0_CLEAR_OC1A,
	TIMER0_SET_OC1A,
}CTC_Output_Mode;

typedef enum
{
	TIMER0_Normal_Port,
	TIMER0_Toggle_OC1A ,
	TIMER0_NON_INVERTING,
	TIMER0_INVERTING,
}PWM_Output_Mode;

typedef enum
{
	TIMER0_NO_CLOCK,
	TIMER0_NO_PRESCALER,
	TIMER0_PRESCALER_8,
	TIMER0_PRESCALER_64,
	TIMER0_PRESCALER_256,
	TIMER0_PRESCALER_1024,
	TIMER0_EXTERNAL_FALLING,
	TIMER0_EXTERNAL_RISING,
}Clock_Pescaler;

typedef enum
{
	TIMER0_DISABLE_INTERRUPT,
	TIMER0_ENABLE_INTERRUPT,
}INTERRUPT_SELECT;

/*******************************************************************************
 *                               Global_Variables Declaration                  *
 *******************************************************************************/


/********************************************************************************
 * Global Array of 4 pointers to function
 * 1.static to use in this file and hold his value
 * 2.volatile to use in ISRs function and in the function 'TIMER0_Set_CallBack'
 * 3.Initial value with Null or use NULL_Ptr in standard_types
 * TIMER0_OVF_vect    : INDEX 0
 * TIMER0_COMP        : INDEX 1
 *********************************************************************************/
static volatile void (*TIMER0_CallBack_Array[2])(void) = {NULL_PTR};



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/**************************************************************************
 * Function Name: TIMER0_Init_Normal_Mode
 * Description  : Initialize Timer0 in Normal Mode or Overflow mode
 * INPUTS       : Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER0_Init_Normal_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);



/**************************************************************************
 * Function Name: TIMER0_Init_CTC_Mode
 * Description  : Initialize Timer0 in Clear timer on compare match(CTC) mode
 * INPUTS       : Compare_Value,OutPutPin_Mode,Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER0_Init_CTC_Mode(uint16 Compare_Value,CTC_Output_Mode OutPutPin_Mode
		                 ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);



/**************************************************************************
 * Function Name: TIMER0_Init_PWM_Mode
 * Description  : Initialize Timer0 in pulse width modulation generation(PWM)mode
 * INPUTS       : Compare_Value(Duty Cycle),OutPutPin_Mode,Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER0_Init_PWM_Mode(uint8 Compare_Value,PWM_Output_Mode OutPutPin_Mode
		                  ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);



/**********************************************************************************
 * Function Name: TIMER0_Set_CallBack
 * Description  : A Function to set the callBack functions for Timer0 Events
 * INPUTS       : ptr_2_fun,index(which indicates which ISR would be Executed)
 * RETURNS      : void
 **********************************************************************************/
void TIMER0_Set_CallBack(void(* ptr_2_fun)(void),uint8 index);

#endif /* TIMER0_H_ */

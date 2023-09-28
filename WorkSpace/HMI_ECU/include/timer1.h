/*===========================================================================================
 * Filename   : timer1.h
 * Author     : Ahmad Haroun
 * Description: Header file ATMEGA32 Timer1 Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/
#ifndef TIMER1_H_
#define TIMER1_H_

#include "gpio.h"
#include <avr/interrupt.h>


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	TIMER1_NORMAL_PORT,
	TIMER1_TOGGLE_OC1A,
	TIMER1_CLEAR_OC1A,
	TIMER1_SET_OC1A,
}CTC_Output_Mode;

typedef enum
{
	TIMER1_Normal_Port,
	TIMER1_Toggle_OC1A ,
	TIMER1_NON_INVERTING,
	TIMER1_INVERTING,
}PWM_Output_Mode;

typedef enum
{
	TIMER1_NO_CLOCK,
	TIMER1_NO_PRESCALER,
	TIMER1_PRESCALER_8,
	TIMER1_PRESCALER_64,
	TIMER1_PRESCALER_256,
	TIMER1_PRESCALER_1024,
	TIMER1_EXTERNAL_FALLING,
	TIMER1_EXTERNAL_RISING,
}Clock_Pescaler;


typedef enum
{
	Timer1_NORMAL_PORT,
	Timer1_CTC_Mode,
}Timer1_Mode;

typedef enum
{
	TIMER1_DISABLE_INTERRUPT,
	TIMER1_ENABLE_INTERRUPT,
}INTERRUPT_SELECT;


typedef enum
{
	FALLING_ICU,
	RAISING_ICU,
}ICU_EDGE_TYPE;


typedef struct
{
	uint16         initial_value;
	uint16         compare_value;            // it will be used in compare mode only.
	Clock_Pescaler prescaler;
	Timer1_Mode    mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                               Global_Variables Declaration                  *
 *******************************************************************************/

/********************************************************************************
 * Global Array of 4 pointers to function
 * 1.static to use in this file and hold his value
 * 2.volatile to use in ISRs function and in the function 'TIMER1_Set_CallBack'
 * 3.Initial value with Null or use NULL_Ptr in standard_types
 * TIMER1_OVF_vect    : INDEX 0
 * TIMER1_COMPA_vect  : INDEX 1
 * TIMER1_COMPB_vect  : INDEX 2
 * TIMER1_CAPT_vect   : INDEX 3
 *********************************************************************************/
static volatile void (*TIMER1_CallBack_Array[4])(void) = {NULL_PTR};



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/**************************************************************************
 * Function Name: TIMER1_Init_Normal_Mode
 * Description  : Initialize Timer1 in Normal Mode or Overflow mode
 * INPUTS       : Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_Normal_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);



/**************************************************************************
 * Function Name: TIMER1_Init_CTC_Mode
 * Description  : Initialize TIMER1 in Clear timer on compare match(CTC) mode
 * INPUTS       : Compare_Value,OutPutPin_Mode,Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_CTC_Mode(uint16 Compare_Value,CTC_Output_Mode OutPutPin_Mode
		                 ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);



/**************************************************************************
 * Function Name: TIMER1_Init_PWM_Mode
 * Description  : Initialize TIMER1 in pulse width modulation generation(PWM)mode
 * INPUTS       : Compare_Value,OutPutPin_Mode,Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_PWM_Mode(uint8 Compare_Value,PWM_Output_Mode OutPutPin_Mode
		                  ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice);

/**************************************************************************
 * Function Name: TIMER1_Init_ICU_Mode
 * Description  : Initialize TIMER1 in ICU_Mode
 * INPUTS       : Prescaler,Interrupt_Choice,EDGE  (1024,Enable_interrupt,Falling)
 * RETURNS      : void
 **************************************************************************/
void TIMER1_Init_ICU_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice,ICU_EDGE_TYPE EDGE);


/**********************************************************************************
 * Function Name: Set_CallBack
 * Description  : A Function to set the callBack functions for Timer1 Events
 * INPUTS       : ptr_2_fun,index(which indicates which ISR would be Executed)
 * RETURNS      : void
 **********************************************************************************/
void TIMER1_Set_CallBack(void(* ptr_2_fun)(void),uint8 index);


/**********************************************************************************
 * Function Name: Timer1_init
 * Description  : A Function to initialze the Timer1
 * INPUTS       : Timer1_ConfigType * Config_Ptr (configuration structure)
 * RETURNS      : void
 **********************************************************************************/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);


/**********************************************************************************
 * Function Name: Timer1_deInit
 * Description  : A Stop Timer1
 * INPUTS       : void
 * RETURNS      : void
 **********************************************************************************/
void Timer1_deInit(void);


/**********************************************************************************
 * Function Name: TIMER1_Set_CallBack
 * Description  : A Function to set the callBack functions for Timer1 Events
 * INPUTS       : ptr_2_fun,index(which indicates which ISR would be Executed)
 * RETURNS      : void
 **********************************************************************************/
void TIMER1_Set_CallBack(void(* ptr_2_fun)(void),uint8 index);


#endif /* TIMER1_H_ */

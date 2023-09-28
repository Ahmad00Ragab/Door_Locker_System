/*===========================================================================================
 * Filename   : timer0.c
 * Author     : Ahmad Haroun
 * Description: Source file ATMEGA32 Timer0 Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/

#include "timer0.h"

/*******************************************************************************
 *                               Global_Variables Declaration                  *
 *******************************************************************************/
volatile uint8 Timer0_Counter_CompareMode = 0;
volatile uint8 Timer0_Counter_NormalMode = 0;
volatile uint8 Timer0_Counter_PWM_Mode = 0;



/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/


#if (0)
/**************************************************************************
 * Function Name: ISR (INTERRUPT HANDLER FOR TIMER0_OVF_vect)
 * Description  : Call the Function that is required to be Executed when TIMER0_OVF happens
 **************************************************************************/
ISR(TIMER0_OVF_vect)
{

	(*TIMER0_CallBack_Array[0])();
}



/**************************************************************************
 * Function Name: ISR (INTERRUPT HANDLER FOR TIMER1_COMPA_vect)
 * Description  : Call the Function that is required to be Executed when TIMER0_COMPA happens
 **************************************************************************/
ISR(TIMER0_COMP_vect)
{
	(*TIMER0_CallBack_Array[1])();
}

#endif



/**************************************************************************
 * Function Name: TIMER0_Init_Normal_Mode
 * Description  : Initialize Timer0 in Normal Mode or Overflow mode
 * INPUTS       : Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER0_Init_Normal_Mode(Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice)
{
	TCNT0 = 0;
	TCCR0 |= (1 << FOC1A);
	TCCR0 &= ~(1<<WGM01) &~(1<<WGM00);
	TCCR0  = (TCCR0 & 0xF8) | (Prescaler);
	if(Interrupt_Choice == TIMER0_DISABLE_INTERRUPT)
	{
		CLEAR_BIT(TIMSK,TOIE0);
	}
	else if(Interrupt_Choice == TIMER0_ENABLE_INTERRUPT)
	{
		SET_BIT(TIMSK,TOIE0);
		SREG |= (1 << 7);
	}
	else
	{

	}
}



/*******************************************************************************
 * Function Name: TIMER0_Init_CTC_Mode
 * Description  : Initialize TIMER0 in Clear timer on compare match(CTC) mode
 * INPUTS       : Compare_Value,OutPutPin_Mode,Prescaler,Interrupt_Choice
 * RETURNS      : void
 ******************************************************************************/
void TIMER0_Init_CTC_Mode(uint16 Compare_Value, CTC_Output_Mode OutPutPin_Mode ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice)
{
	DDRB |= (1 << PB3); /* Make OC0 OUTPUT */
	TCNT0 = 0;
	OCR0  = Compare_Value;
	TCCR0 |=(1 << FOC0) ;
	TCCR0 |= (1 << WGM01);
	TCCR0  = (TCCR0 & 0xF8) | (Prescaler);
	TCCR0  = (TCCR0 & 0xCF) | (OutPutPin_Mode << 4);
	if(Interrupt_Choice == TIMER0_DISABLE_INTERRUPT)
	{
		CLEAR_BIT(TIMSK,OCIE0);
	}
	else if(Interrupt_Choice == TIMER0_ENABLE_INTERRUPT)
	{
		SET_BIT(TIMSK,OCIE0);
		SREG |= (1 << 7);
	}
	else
	{

	}

}


/**************************************************************************
 * Function Name: TIMER1_Init_PWM_Mode
 * Description  : Initialize TIMER1 in pulse width modulation generation(PWM)mode
 * INPUTS       : Compare_Value,OutPutPin_Mode,Prescaler,Interrupt_Choice
 * RETURNS      : void
 **************************************************************************/
void TIMER0_Init_PWM_Mode(uint8 Compare_Value,PWM_Output_Mode OutPutPin_Mode
		                  ,Clock_Pescaler Prescaler,INTERRUPT_SELECT Interrupt_Choice)
{
	DDRB |= (1 << PB3); /* Make OC0 OUTPUT */
	TCNT0 = 0;
	OCR0  = Compare_Value;
	TCCR0 &= ~(1<<FOC0);
	TCCR0 |= (1<<WGM00)|(1 <<WGM01);
	TCCR0  = (TCCR0 & 0xF8) | (Prescaler);
	TCCR0  = (TCCR0 & 0xCF) | (OutPutPin_Mode << 4);

	if(Interrupt_Choice == TIMER0_DISABLE_INTERRUPT)
	{
		CLEAR_BIT(TIMSK,OCIE0);
	}
	else if(Interrupt_Choice == TIMER0_ENABLE_INTERRUPT)
	{
		SET_BIT(TIMSK,OCIE0);
		SREG |= (1 << 7);
	}
	else
	{

	}
}



/**********************************************************************************
 * Function Name: TIMER0_Set_CallBack
 * Description  : A Function to set the callBack functions for Timer1 Events
 * INPUTS       : ptr_2_fun,index(which indicates which ISR would be Executed)
 * RETURNS      : void
 **********************************************************************************/
void TIMER0_Set_CallBack(void(* ptr_2_fun)(void),uint8 index)
{
	TIMER0_CallBack_Array[index] = ptr_2_fun;
}

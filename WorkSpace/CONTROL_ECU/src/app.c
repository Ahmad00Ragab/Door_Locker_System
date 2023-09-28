/*===========================================================================================
 * Filename   : app.c
 * Author     : Ahmad Haroun
 * Description: Source file for the application Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/
#include "app.h"
#include "gpio.h"
#include <avr/delay.h>
#include "buzzer.h"
#include "buzzer.h"
#include "motor.h"
#include "external_eeprom.h"
#include "timer1.h"
#include "twi.h"
#include "uart.h"

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

/* used to indicate the password size, to know how many bytes to read form EEPROM*/
uint8 pass_size = 0;

/* used to store the required number of ticks of timer1 to generate a certain delay*/
volatile uint8 ticks = 0;



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/**************************************************************************
 * Function Name: APP_init
 * Description  : This function is responsible for initializing the peripherals
 *                (TWI && DC MOTOR && UART && BUZZER)
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void APP_init(void)
{

	UART_ConfigType config =  {Character_8_bit, Parity_Disabled,Stop_One_bit, 9600};

	TWI_ConfigType TWI_Config = {0x01,400000};

	/* Enable Global Interrupt */
	SREG |= (1<<7);

	TWI_init(&TWI_Config);

	DcMotor_Init();

	UART_init(&config);

	Buzzer_init();
}


/**************************************************************************
 * Function Name: APP_start
 * Description  : This function is responsible for Running the system as required
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void APP_start(void)
{
	/* used to identify the required operation sent by HMI_ECU */
	uint8 operation_id;

	operation_id = UART_recieveByte();

	switch(operation_id)
	{
	case '0':	/* Setting a new password operation */
		setPassword();
		break;

	case '1':	/* Check if user entered password is correct */
		verifyPassword();
		break;


	case'2':	/* open gate operation */
		openGate();
		break;


	case '3':	/* lock the system */
		lockSystem();
		break;
	}
}


/**************************************************************************
 * Function Name: setPassword
 * Description  : This function is responsible for setting and updating
 *                the password of the system
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void setPassword(void)
{
	uint8 received_pass[10] = "";

	uint8 i;
	/* reset pass_size , i */
	pass_size = 0;
	i = 0;

	/* store the user entered password */
	UART_receiveString(received_pass);

	/* store password in eeprom */
	while(received_pass[i])
	{
		EEPROM_writeByte(EEPROM_PASSWORD_LOCATION+i,received_pass[i]);
		_delay_ms(10);
		pass_size++;
		i++;
	}
}


/**************************************************************************
 * Function Name: verifyPassword
 * Description  : The function is to check if the passed two passwords are identical
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void verifyPassword(void)
{
	/* isMathed is a flag that is set when password is correct,
	 * i is a counter used when reading from EEPROM
	 */
	uint8 i;
	boolean isMatched;
	uint8 received_pass[10] = "";


	uint8 stored_pass[10] = ""; /* to store the password extracted from EEPROM */


	/* store the user entered password */
	UART_receiveString(received_pass);

	/* extract saved password from EEPROM */
	for(i = 0; i < pass_size; i++)
	{
		EEPROM_readByte(EEPROM_PASSWORD_LOCATION + i, &stored_pass[i]);
		_delay_ms(10);
	}

	/* check if the user entered password && stored password are identical */
	isMatched = isPassMatched(received_pass, stored_pass, pass_size);
	if(isMatched == TRUE)
	{
		/* if matched, send '1' */
		UART_sendByte('1');
	}
	else
	{
		/* if not matched, send '0' */
		UART_sendByte('0');
	}

}


/**************************************************************************
 * Function Name: isPassMatched
 * Description  : This function is to compare user entered password && system password
 * INPUTS       : void
 * RETURNS      : uint8
 * 			      TRUE  ==> Passwords match
 * 			      FALSE ==> Passwords do not match
 **************************************************************************/
uint8 isPassMatched(uint8 * pass1, uint8 * pass2, uint8 size)
{
	uint8 i ;
	boolean matched = TRUE;
	for(i = 0; i < size; ++i)
	{
		if(pass1[i] != pass2[i])
		{
			matched = FALSE;
			break;
		}
	}

	return matched;
}


/**************************************************************************
 * Function Name: TIMER1_delay_15sec
 * Description  : This function is to generate 15 seconds delay using timer1.
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TIMER1_delay_15sec(void)
{
	/* Timer operates in CTC mode, required OCR value to generate 15 seconds
	 * at 1024 pre-scaler is 58594 for 2 times,
	 * for TCNT1 element is configuration can be any dummy number'1000'*/
	Timer1_ConfigType config = { 0 , 58594, TIMER1_PRESCALER_1024, Timer1_CTC_Mode};
	Timer1_init(&config);

	TIMER1_Set_CallBack(TIMER1_callback_function,1);

	while(ticks < 2);

	ticks = 0;

	Timer1_deInit();
}


/**************************************************************************
 * Function Name: TIMER1_delay_3sec
 * Description  : This function is to generate 3 seconds delay using timer1.
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TIMER1_delay_3sec(void)
{
	/* (3_SEC) == 23436 timer counts */
	/* Timer operates in CTC mode, required OCR value to generate 3 seconds
	 * at 1024 pre-scaler is 23450,
	 * for TCNT1 element is configuration can be any number*/
	Timer1_ConfigType config = {0,23436, TIMER1_PRESCALER_1024, Timer1_CTC_Mode};
	Timer1_init(&config);

	/* set callback function for timer1 interrupt */
	TIMER1_Set_CallBack(TIMER1_callback_function,1);

	/* wait for timer interrupt */
	while(ticks == 0);

	/* reset ticks variable for next future use */
	ticks = 0;

	Timer1_deInit();
}


/**************************************************************************
 * Function Name: TIMER1_callback_function
 * Description  : The required function to be executed when timer interrupt
 *                is fired, "increments ticks variable"
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TIMER1_callback_function(void)
{
	ticks++;
}



/**************************************************************************
 * Function Name: lockSystem
 * Description  : This function is responsible for locking the system
 *                In case of password entered is wrong for 3 times
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void lockSystem(void)
{
	/* The control ECU is required to turn on the buzzer for 1 minute when system
	 * goes to the locked state
	 */
	uint8 timer_counter;	/* used to repeat the 15sec delay function to get 1 minute */

	/* turn on buzzer for 1 minute */
	Buzzer_on();
	for(timer_counter = 0; timer_counter < 4; timer_counter++)
	{
		TIMER1_delay_15sec();
	}
	Buzzer_off();
}


/**************************************************************************
 * Function Name: openGate
 * Description  : This function is responsible to open the door
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void openGate(void)
{
	/* open the door by rotating the DC motor CW for 15 seconds */
	DcMotor_Rotate(rotate_CW,100);
	TIMER1_delay_15sec();

	/* keep the door open for 3 seconds */
	DcMotor_Rotate(stop,100);
	TIMER1_delay_3sec();

	/* lock the door by rotating the DC motor ACW for 15 seconds */
	DcMotor_Rotate(rotate_A_CW,100);
	TIMER1_delay_15sec();

	/* stop the motor */
	DcMotor_Rotate(stop,100);
}

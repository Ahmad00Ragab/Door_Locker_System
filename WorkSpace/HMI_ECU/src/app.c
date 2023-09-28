/*===========================================================================================
 * Filename   : app.c
 * Author     : Ahmad Haroun
 * Description: Source file for the application Driver
 * Created on : SEP 4, 2023
 *==========================================================================================*/
#include "app.h"
#include "lcd.h"
#include <avr/delay.h>
#include "uart.h"
#include "keypad.h"
#include "timer1.h"


/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

volatile uint8 ticks = 0;     /* used to indicate the required timer ticks to meet
 * the required delay time
 */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/**************************************************************************
 * Function Name: APP_init
 * Description  : This function is responsible for initializing the peripherals
 *                (LCD && UART) and Setting the Password for 1st time
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void APP_init(void)
{
	/* Crate a UART configuration Structure with the required properties */
	UART_ConfigType config = {Character_8_bit, Parity_Disabled,Stop_One_bit,9600};

	/* Enable Global Interrupt */
	SREG |= (1<<7);

	/* initialize LCD, UART modules */
	LCD_init();

	UART_init(&config);

	/* set password at startup */
	setPass();
}


/**************************************************************************
 * Function Name: APP_start
 * Description  : This function is responsible for Running the system as required
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void APP_start(void)
{
	boolean isCorrect;		/* used to check if entered password matches system password */
	uint8 input = '\0'; 	/* used to get the user required action */


	/* Display main system options */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, " + : Open Door");
	LCD_displayStringRowColumn(1, 0, " - : Change Pass");

	/* get user required action, keep prompting till a valid input is entered */
	do
	{
		input = KEYPAD_getPressedKey();
	}while(input != '+' && input != '-');

	/* ask user for system password with 3 trials allowance */
	isCorrect = checkPassword_trials();
	if(isCorrect == FALSE)
	{
		/* all the 3 trials are used, lock the system */
		lockSystem();

		/* go to step 2 "main menu options"*/
		return;
	}

	/* Execute the required action */
	if('+' == input)
	{
		openDoor();
	}
	else
	{
		/* change the password */
		setPass();
	}
}


/**************************************************************************
 * Function Name: setPassword
 * Description  : This function is responsible for setting and updating
 *                the password of the system
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void setPass(void)
{
	uint8 pass1[10] = ""; /* to store the first password */
	uint8 pass2[10] = ""; /* to store the confirmation password */
	uint8 pass1_size = 0; /* indicates pass1 length */
	uint8 pass2_size = 0; /* indicates pass2 length */

	boolean matched = FALSE;	  /* flag that is set when pass1 && pass2 are identical */

	do
	{
		/* prompt user for password */
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "Plz enter pass: ");
		LCD_moveCursor(1, 0);

		/* get the password for the first time */
		getPass(pass1, &pass1_size);

		/* prompt user to confirm the password */
		LCD_displayStringRowColumn(0, 0, "Plz re-enter the");
		LCD_displayStringRowColumn(1, 0, "same pass: ");

		/* get the password for the second time */
		getPass(pass2, &pass2_size);

		/* Check if the two passwords match*/
		if(pass1_size != pass2_size)
		{
			/* if the two passwords are of different sizes, they are already mismatched */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "Error!! ");
			LCD_displayStringRowColumn(1, 0, "NOT MATCHED");
			_delay_ms(1000);
			continue;
		}
		else
		{
			/* if the 2 passwords are the same size, check if they match */
			matched = isPassMatched(pass1, pass2, pass1_size);

			LCD_clearScreen();

			if(matched == TRUE)
			{
				/* if matched, send the password to the Control_ECU to be stored in EEPROM */
				LCD_displayStringRowColumn(0, 0, "Pass set");
				LCD_displayStringRowColumn(1, 0, "Successfully");

				UART_sendByte('0');
				UART_sendString(pass1);

			}
			else
			{
				/* if not matched, print error messages and prompt from the beginning */
				LCD_displayStringRowColumn(0, 0, "Error!! ");
				LCD_displayStringRowColumn(1, 0, "NOT MATCHED");
			}
			TIMER1_delay_1sec();
		}
	}while(matched == FALSE); /* keep prompting for a correct password to be set */
}


/**************************************************************************
 * Function Name: checkPassword_trials
 * Description  : This function is responsible for prompting the user for correct passwords,
 * 		          within maximum 3 times.
 * INPUTS       : void
 * RETURNS      : uint8
 *                1 Password is correct.
 * 		   	      0 All trials are used without password being correct
 **************************************************************************/
uint8 checkPassword_trials(void)
{
	uint8 maxTrials;
	uint8 isCorrect;

	for(maxTrials = 3; maxTrials > 0; maxTrials--)
	{
		/* prompt user to enter the system password to execute the required action,
		 * then check if password is correct
		 */
		isCorrect = verifyPass_ControlECU();

		if ('1' == isCorrect)
		{
			/* password is correct */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "ACCESS GRANTED");
			TIMER1_delay_1sec();
			return 1;
		}
		else
		{
			/* if password is false */
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, "ACCESS DENIED");
			TIMER1_delay_1sec();
		}
	}
	/* all 3 trials are used without password being correct */
	return 0;
}



/**************************************************************************
 * Function Name: openDoor
 * Description  : This function is responsible for executing the steps required to open the door
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void openDoor(void)
{
	int count_down = 3;
	/* Send a command to control_ECU to open the door */
	UART_sendByte('2');
	/* display opening message for 15 seconds */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is Unlocking");
	TIMER1_delay_15sec();

	/* display time remaining to lock the door */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door locks in");
	LCD_displayStringRowColumn(1, 8, "3");

	while(count_down--)
	{
		/* update count_down variable every 1 second */
		TIMER1_delay_1sec();
		LCD_moveCursor(1, 8);
		LCD_intgerToString(count_down);
	}

	/* display locking the door warning */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is locking  ");
	TIMER1_delay_15sec();
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
	uint8 timer_counter ; /* used to repeat the 15sec delay function to get 1 min*/
	/* activate buzzer for 1 minute "send relative signal to control_mcu" */
	UART_sendByte('3');

	/* display error message on lcd for 1 minute */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "MAX TRIALS USED");
	LCD_displayStringRowColumn(1, 0, "SYSTEM IS LOCKED");
	/* no input received */

	/* Delay 1 minute */
	for(timer_counter = 0; timer_counter < 4; timer_counter++)
	{
		TIMER1_delay_15sec();
	}
}



/**************************************************************************
 * Function Name: verifyPass_ControlECU
 * Description  : This function is to compare password entered by user to
 *                the saved password of the system
 * INPUTS       : void
 * RETURNS      : uint8
 *                '1' Password is correct.
 * 		   	      '0' Password is false.
 **************************************************************************/
uint8 verifyPass_ControlECU(void)
{
	uint8 response = 0;		/* flag that is set if entered password matches the system password */
	uint8 pass[10] = "";	/* to store the user entered password */
	uint8 pass_size = 0;	/* to indicate the user entered password size */

	/* prompt for password */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Plz enter pass:");
	LCD_moveCursor(1, 0);

	/* get user entered password */
	getPass(pass, &pass_size);

	/* send the password to the Control_ECU to be check with system password */
	UART_sendByte('1');
	_delay_ms(10);
	UART_sendString(pass);

	/* receive Control_ECU response */
	response = UART_recieveByte();
	return response;
}



/**************************************************************************
 * Function Name: getPass
 * Description  : This function is responsible for storing the user entered password,
 * 		          and printing '*' on LCD instead of each entered character
 * INPUTS       : password array && Size of password passed by address
 * RETURNS      : void
 **************************************************************************/
void getPass(uint8 *passArr, uint8 *size)
{
	_delay_ms(100);

	*size = 0;
	do
	{
		passArr[*size] = KEYPAD_getPressedKey();	/* store the entered keypad character in the array,increment its size */
		(*size)++;
		if(passArr[(*size) - 1] != 13)
		{
			LCD_displayCharacter('*');		/* print '*' on LCD in place of the entered keypad value, ignore ON key press */
		}
		_delay_ms(250);				       /* wait 250 between two keypad presses */
	}while(passArr[(*size) - 1] != 13);   /* keep storing characters till ON key is pressed */
	passArr[--(*size)] = '\0'; /* terminate input string by null character, remove the enter character */

}


/**************************************************************************
 * Function Name: isPassMatched
 * Description  : This function is to compare user entered password && system password
 * INPUTS       : void
 * RETURNS      : uint8
 * 			      1 ==> Passwords match
 * 			      0 ==> Passwords do not match
 **************************************************************************/
uint8 isPassMatched(uint8 * pass1, uint8 * pass2, uint8 size)
{
	uint8 i;
	boolean matched = TRUE;
	for(i = 0 ; i < size; ++i)
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
	/* (7.5 SEC) == 58594 */
	Timer1_ConfigType config = {0,58594,TIMER1_PRESCALER_1024,Timer1_CTC_Mode};
	Timer1_init(&config);
	TIMER1_Set_CallBack(TIMER1_callback_function,1);
	while(ticks < 2);
	ticks = 0;
	Timer1_deInit();
}



/**************************************************************************
 * Function Name: TIMER1_delay_3sec
 * Description  : This function is to generate 1 seconds delay using timer1.
 * INPUTS       : void
 * RETURNS      : void
 **************************************************************************/
void TIMER1_delay_1sec(void)
{
	/* required OCR value to generate 1 second at 1024 pre-scaler is 7813*/
	/* Timer will run in CTC, so we can put any number in TCNT1 for the config*/
	Timer1_ConfigType config = {0,7813,TIMER1_PRESCALER_1024, Timer1_CTC_Mode};
	Timer1_init(&config);

	/* set timer callback function */
	TIMER1_Set_CallBack(TIMER1_callback_function,1);
	/* wait for timer to generate the interrupt */
	while(ticks == 0)
	{

	};

	/* reset ticks variable for the next future use */
	ticks = 0;

	/* reset timer1 configurations */
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




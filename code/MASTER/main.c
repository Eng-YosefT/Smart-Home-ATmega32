/**************************************************/
/*Desc   : main file for Master mivcrocontroller  */
/*Author : Youssef Taha Moawad		              */
/*Date   : 16 sep 2023                            */
/*Version: 1.0V                                   */
/**************************************************/

#include "main_config.h"
#include "LCD.h"
#include "timer_driver.h"
#include "keypad_driver.h"
#include "SPI.h"
#include "LED.h"
#include "menu.h"
#include <avr/io.h>
#include <avr/delay.h>
volatile uint16 session_counter = 0;//indicate session time
uint8 timeout_flag = FALSE;//stores if the session is still valid
uint8 LOGIN_BLOCKED  =  FALSE;
uint8 temperature = 0;//The average temperature of the room
uint8 temp_ones = NOT_SELECTED;//The entered right number of the temperature
uint8 temp_tens = NOT_SELECTED;//The entered left number of the temperature
uint8 login_mode = NO_MODE; //Store the current user mode admin or guest or not logged in
uint8 block_mode_flag = FALSE;//is true if the login is blocked or false if not blocked
uint8 key_pressed = NOT_PRESSED;
uint8 pass_tries_count=0;
uint8 pass_counter=0;//counts the entered key of the password from the keypad
uint8 pass[PASS_SIZE];
/*Setting Admin and Guest passwords  */
/********************************* setting Admin password **********************************************/
uint8 Adminpass[PASS_SIZE]= ADMIN_PASS ;
/********************************* setting guest password **********************************************/
uint8 Gestpass[PASS_SIZE]= GEST_PASS ;
//The The End of if admin and guest password is set

int main(void)
{
	/*  INITIALIZE  */
	initializeSystem();

	/* Printing Welcome screen */
	printWelcomeScreen();





	if (SITPASS!=TRUE)
	{

		LCD_vSend_string("Login for");//printing login menu
		LCD_movecursor(2,1);
		LCD_vSend_string("first time");
		_delay_ms(1000);


		/********************************* setting Admin password **********************************************/
		setAdminPassword();
		/********************************* setting guest password **********************************************/
		setGestPassword();
	}
	block_mode_flag = LOGIN_BLOCKED;


	while (1)//The start of the periodic code
	{
		key_pressed = NOT_PRESSED;//return the variable that holds the pressed key from keypad to its initial value
		uint8 pass_tries_count=0;//stores how many times the user tried to log in to the system and failed

		if ( timeout_flag==TRUE )
		{
			timer0_stop();//stop the timer that increase the session counter
			session_counter = 0;
			timeout_flag=FALSE;
			login_mode=NO_MODE;
			key_pressed = NOT_PRESSED;
			LED_vTurnOff(GUEST_LED_PORT,GUEST_LED_PIN);//turnoff the led of the guest
			LED_vTurnOff(ADMIN_LED_PORT,ADMIN_LED_PIN);//turnoff the led of the admin
			LCD_clearscreen();
			LCD_vSend_string("Session Timeout");//print session timeout message
			_delay_ms(1000);
		}
		while (login_mode==NO_MODE)
		{
			if(block_mode_flag==TRUE)//if the login process was blocked wait till the The End of the block period
			{
				LCD_clearscreen();
				LCD_vSend_string("Login blocked");
				LCD_movecursor(2,1);
				LCD_vSend_string("wait 20 seconds");
				LED_vTurnOn(BLOCK_LED_PORT,BLOCK_LED_PIN);//Turn on the led of Blocked
				_delay_ms(BLOCK_MODE_TIME);
				pass_tries_count = 0;
				block_mode_flag = FALSE ;
				LED_vTurnOff(BLOCK_LED_PORT,BLOCK_LED_PIN);//Turn off the led of Blocked
				LOGIN_BLOCKED = FALSE ;
			}
			LCD_clearscreen();
			LCD_vSend_string("Select mode :");
			LCD_movecursor(2,1);
			LCD_vSend_string("0:Admin 1:Guest");
			while(key_pressed==NOT_PRESSED)
			{
				key_pressed = keypad_u8check_press();
			}
			if ( key_pressed!=CHECK_ADMIN_MODE && key_pressed!=CHECK_GUEST_MODE )
			{
				LCD_clearscreen();
				LCD_vSend_string("Wrong input.");
				key_pressed = NOT_PRESSED;
				_delay_ms(1000);
				continue;//return to the loop of login #while (login_mode==NO_MODE)
			}


			switch(key_pressed)
			{
			/********************************* Admin login **********************************************/
			case CHECK_ADMIN_MODE:
				AdiminLogin();
				break;//bREAK SWITCH case
				/********************************* case Guest login **********************************************/
			case  CHECK_GUEST_MODE:

				GistLogin();
				break;//break for CHECK_GUEST_MODE switch case
			}//The End of switch

		}

		/*************************************************************************************************/
		uint8 show_menu = MAIN_MENU;


		while(timeout_flag!=TRUE)//Show the menu in case of the time is not out
		{
			key_pressed = NOT_PRESSED;//Set the key pressed by the user to its default value
			switch (show_menu)
			{
			case MAIN_MENU:
				do
				{
					/******************** print main Menu ******************/
					LCD_clearscreen();
					LCD_vSend_string("1:Light ");

					if(login_mode==ADMIN)//check login mode
					{
						LCD_vSend_string("  2:Pass");
						LCD_movecursor(2,1);
						LCD_vSend_string("3:Air Cond  4:TV");//this menu options only printed if the logged in user is an admin
					}

					/*******************************************************/

					key_pressed = u8GetKeyPressed(login_mode);
					_delay_ms(100);

					if (key_pressed == SELECT_LIGHT_CONTROL)// key pressed is 1
					{
						show_menu = LIGHT_CONTROL_MENU;
					}
					else if (key_pressed == SELECT_PASSWORD && login_mode == ADMIN)// key pressed is 2 and the logged in user is admin
					{
						show_menu = PASSWORD_MENU;//shown to more menu
					}
					else if (key_pressed == SELECT_AIR_CONDITIONING && login_mode == ADMIN)// key pressed is 3 and the logged in user is admin
					{
						show_menu = AIRCONDITIONING_MENU;//shown to more menu
					}
					else if (key_pressed == SELECT_TV && login_mode == ADMIN)// key pressed is 4 and the logged in user is admin
					{
						show_menu = TV_MENU;
					}

					else if(key_pressed != NOT_PRESSED)//show wrong input message if the user pressed wrong key
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong input");
						_delay_ms(500);
					}
				} while ( ((key_pressed < '1') || (key_pressed > '4') ) && (timeout_flag == FALSE) );//break the loop in case of valid key or time is out

				break;//The End of main 


			case LIGHT_CONTROL_MENU:
				do
				{
					/******************** print more Menu ******************/
					LCD_clearscreen();
					LCD_vSend_string("1:Room1 2:Room2");
					LCD_movecursor(2,1);
					LCD_vSend_string("3:Room3 4:Room4");
					/*******************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(100);

					if (key_pressed == SELECT_ROOM1)// key pressed is 1
					{
						show_menu = ROOM1_MENU;//shown to room1 menu
					}
					else if (key_pressed == SELECT_ROOM2)// key pressed is 2
					{
						show_menu = ROOM2_MENU;//shown to room2 menu
					}
					else if (key_pressed == SELECT_ROOM3)// key pressed is 3
					{
						show_menu = ROOM3_MENU;//shown to room3 menu
					}
					else if (key_pressed == SELECT_ROOM4 )// key pressed is 4
					{
						show_menu = ROOM4_MENU;//shown to room4 menu
					}
					else if(key_pressed != NOT_PRESSED)//show wrong input message if the user pressed wrong key
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong input");
						_delay_ms(500);
					}

				} while (( (key_pressed < '1') || (key_pressed > '4') ) && (timeout_flag == FALSE));//break the loop in case of valid key or time is out

				break;//The End of light 
			case PASSWORD_MENU:
				do
				{
					/******************** print more Menu ******************/
					LCD_clearscreen();
					LCD_vSend_string("ChangePass 0:Ret");
					LCD_movecursor(2,1);
					LCD_vSend_string("1:Admin  2:Guest ");
					/*******************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(100);

					if (key_pressed == SELECT_CHNG_ADMIN_PASS)
					{
						show_menu = CHNG_ADMIN_PASS_MENU;
					}
					else if (key_pressed == SELECT_CHNG_GUEST_PASS)
					{
						show_menu = CHNG_GUEST_PASS_MENU;
					}
					else if (key_pressed == SELECT_PASS_RET)// key pressed is 0
					{
						show_menu = MAIN_MENU;//shown to more menu
					}
					else if(key_pressed != NOT_PRESSED)
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong input");
						_delay_ms(500);
					}
				} while (( (key_pressed < '0') || (key_pressed > '2') ) && (timeout_flag == FALSE));//break the loop in case of valid key or time is out
				break;//The End of air conditioning 
			case CHNG_ADMIN_PASS_MENU:
				LCD_clearscreen();
				setAdminPassword();
				show_menu = MAIN_MENU;//shown to main menu
				break;//The End of sit admin password case
			case CHNG_GUEST_PASS_MENU:
				LCD_clearscreen();
				setGestPassword();
				show_menu = MAIN_MENU;//shown to main menu
				break;//The End of sit guest password case
			case AIRCONDITIONING_MENU:
				do
				{
					/******************** print more Menu ******************/
					LCD_clearscreen();
					LCD_vSend_string("1:Set temperature ");
					LCD_movecursor(2,1);
					LCD_vSend_string("2:Control  0:RET");
					/*******************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(100);

					if (key_pressed == SELECT_SET_TEMPERATURE)// key pressed is 1
					{
						show_menu = TEMPERATURE_MENU;//shown to set temperature menu
					}
					else if (key_pressed == SELECT_AIR_COND_CTRL)// key pressed is 2
					{
						show_menu = AIRCOND_CTRL_MENU;//shown to air conditioning control menu
					}
					else if (key_pressed == SELECT_AIR_COND_RET)// key pressed is 0
					{
						show_menu = MAIN_MENU;//shown to more menu
					}
					else if(key_pressed != NOT_PRESSED)//show wrong input message if the user pressed wrong key
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong input");
						_delay_ms(500);
					}
				} while (( (key_pressed < '0') || (key_pressed > '2') ) && (timeout_flag == FALSE));//break the loop in case of valid key or time is out
				break;//The End of air conditioning 

			case ROOM1_MENU:
				vMenuOption(ROOM1_MENU,login_mode);//call the function that show the menu of room 1
				show_menu = MAIN_MENU;//shown to main menu
				break;//The End of room1 

			case ROOM2_MENU:
				vMenuOption(ROOM2_MENU,login_mode);//call the function that show the menu of room 2
				show_menu = MAIN_MENU;//shown to main menu
				break;//The End of room2 

			case ROOM3_MENU:
				vMenuOption(ROOM3_MENU,login_mode);//call the function that show the menu of room 3
				show_menu = MAIN_MENU;//shown to main menu
				break;//The End of room3 

			case ROOM4_MENU:
				vMenuOption(ROOM4_MENU,login_mode);//call the function that show the menu of room 4
				if (login_mode == GUEST)//in case of guest is logged in
				{
					show_menu = MAIN_MENU;//shown to main menu
				}
				break;//The End of room4 

			case TV_MENU:
				vMenuOption(TV_MENU,login_mode);//call the function that show the menu of tv
				show_menu = MAIN_MENU;//shown to more menu
				break;//The End of TV 

			case AIRCOND_CTRL_MENU:
				vMenuOption(AIRCOND_CTRL_MENU,login_mode);//call the function that show the menu of Air conditioning control
				show_menu = AIRCONDITIONING_MENU;//shown to air conditioning menu
				break;//The End of air conditioning control 

			case TEMPERATURE_MENU:
				temperature = 0;//clear the value of temperature
				while (temperature==0 && timeout_flag == FALSE)//start the loop that asks for the temperature from the user in case of the time is not out
				{
					key_pressed = NOT_PRESSED;
					LCD_clearscreen();
					LCD_vSend_string("Set temp.:__ ");//print the format of inserting temperature
					LCD_vSend_char(DEGREES_SYMBOL); // print the symbol of degree
					LCD_vSend_char('C'); // print the C character
					LCD_movecursor(1,11);//move the cursor to the place to write the entered temperature
					_delay_ms(200);
					/*******************************************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(250);

					if (timeout_flag == TRUE) //in case of the time is out before the user press a key
					{
						break;//break the loop that ask for temperature
					}
					if (key_pressed <'0' || key_pressed >'9')//show wrong input message if the user entered non numeric value
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong input");
						_delay_ms(500);
						continue;//return to #while (temperature==0)
					}
					else//if the value is valid
					{
						LCD_vSend_char(key_pressed);//print the value on the lcd
						temp_tens = key_pressed-ASCII_ZERO;//save the entered value
						key_pressed = NOT_PRESSED;
					}
					/*******************************************************************************/
					key_pressed = u8GetKeyPressed(login_mode);//wait for the user till key is pressed or the time is out
					_delay_ms(250);

					if (timeout_flag == TRUE)//if the user session is timeout
					{
						break;//break the loop that ask for temperature
					}
					if ((key_pressed <'0' || key_pressed >'9'))//show wrong input message if the user entered non numeric value
					{
						LCD_clearscreen();
						LCD_vSend_string("Wrong input");
						_delay_ms(500);
						continue;//repeat the loop that ask for the temperature
					}
					else//if the value is valid
					{
						LCD_vSend_char(key_pressed);//print the value on the lcd
						temp_ones = key_pressed-ASCII_ZERO;//save the entered value
						key_pressed = NOT_PRESSED;
					}
					temperature = temp_tens*10 + temp_ones;//set the value of the temperature from the given separated values
					SPI_ui8TransmitRecive(SET_TEMPERATURE);//Send the code of set temperature
					_delay_ms(200);//Halt the system to prevent write collision
					SPI_ui8TransmitRecive(temperature);//send the entered temperature
					LCD_clearscreen();
					LCD_vSend_string("Temperature Sent");//show the message
					_delay_ms(500);
				}
				show_menu = AIRCONDITIONING_MENU;//shown to air conditioning menu
				break;//break from switch
			}//The End of the switch
		}//The End of while that repeats the menu after each successful action till session timeout
	}// The End of the main while(1)
}//The End of main function

ISR(TIMER0_COMP_vect)
{
	session_counter++;//increase the indicator of session time for every tick
}

void initializeSystem(void)
{
	// Initialize hardware
	/*****************  INITIALIZE  ***********************/
	LED_vInit(ADMIN_LED_PORT,ADMIN_LED_PIN);//initializes the led of admin
	LED_vInit(GUEST_LED_PORT,GUEST_LED_PIN);//initializes the led of guest
	LED_vInit(BLOCK_LED_PORT,BLOCK_LED_PIN);//initializes the led of block
	LCD_vInit();//initializes the LCD screen
	keypad_vInit();//initializes the keypad
	SPI_vInitMaster();//initializes the communication protocol of SPI
	/******************************************************/
	// You may need to configure hardware peripherals and load passwords here
}
void printWelcomeScreen(void)
{
	/* Printing Welcome screen */
	LCD_vSend_string("Welcome to smart");
	LCD_movecursor(2,1);
	LCD_vSend_string("home system");
	_delay_ms(1000);
	LCD_clearscreen();//remove all and move the cursor to the first column of the first row
}
void setAdminPassword(void)
{
	LCD_clearscreen();
	LCD_vSend_string("Set Admin pass");
	LCD_movecursor(2,1);
	LCD_vSend_string("Admin pass:");
	key_pressed = NOT_PRESSED;
	pass_counter=0;

	for ( pass_counter = 0; pass_counter < PASS_SIZE; pass_counter++)
	{
		Adminpass[pass_counter]= NOT_STORED;
	}
	pass_counter=0;
	while (pass_counter<PASS_SIZE)//loop till the user finish inserting the pass
	{

		key_pressed = NOT_PRESSED;//return the variable that holds the pressed key from keypad to its initial value
		while (key_pressed == NOT_PRESSED)//repeat till the user press any key
		{
			key_pressed = keypad_u8check_press();//if the user pressed any button in keypad save the value in key_pressed
		}

		Adminpass[pass_counter]= key_pressed-ASCII_ZERO; //add the entered character to the pass array
		LCD_vSend_char(key_pressed);//print the entered character
		_delay_ms(CHARACTER_PREVIEW_TIME);
		LCD_movecursor(2,12+pass_counter);
		LCD_vSend_char(PASSWORD_SYMBOL);
		_delay_ms(100);
		pass_counter++;
	}

	LCD_clearscreen();
	LCD_vSend_string("Pass Saved");
	_delay_ms(500);
	LCD_clearscreen();
	LOGIN_BLOCKED=FALSE;
}
void setGestPassword(void)
{
	LCD_clearscreen();
	LCD_vSend_string("Set Guest Pass");
	LCD_movecursor(2,1);
	LCD_vSend_string("Guest Pass:");

	key_pressed = NOT_PRESSED;
	pass_counter=0;

	for ( pass_counter = 0; pass_counter < PASS_SIZE; pass_counter++)
	{
		Gestpass[pass_counter]= NOT_STORED;
	}
	pass_counter=0;
	while (pass_counter<PASS_SIZE)//loop till the user finish inserting the pass
	{

		key_pressed = NOT_PRESSED;//return the variable that holds the pressed key from keypad to its initial value
		while (key_pressed == NOT_PRESSED)//repeat till the user press any key
		{
			key_pressed = keypad_u8check_press();//if the user pressed any button in keypad save the value in key_pressed
		}

		Gestpass[pass_counter]= key_pressed-ASCII_ZERO; //add the entered character to the pass array
		LCD_vSend_char(key_pressed);//print the entered character
		_delay_ms(CHARACTER_PREVIEW_TIME);
		LCD_movecursor(2,12+pass_counter);
		LCD_vSend_char(PASSWORD_SYMBOL);
		_delay_ms(100);
		pass_counter++;
	}

	LCD_clearscreen();
	LCD_vSend_string("Pass Saved");
	_delay_ms(500);
	LCD_clearscreen();
	LOGIN_BLOCKED=FALSE;
}
void AdiminLogin(void)
{
	while(login_mode!=ADMIN)
	{
		key_pressed = NOT_PRESSED;
		LCD_clearscreen();
		LCD_vSend_string("Admin mode");
		LCD_movecursor(2,1);
		LCD_vSend_string("Enter Pass:");
		_delay_ms(200);
		pass_counter=0;
		while(pass_counter<PASS_SIZE)
		{
			while (key_pressed == NOT_PRESSED)
			{
				key_pressed = keypad_u8check_press();
			}
			pass[pass_counter]=key_pressed-ASCII_ZERO;
			LCD_vSend_char(key_pressed);
			_delay_ms(CHARACTER_PREVIEW_TIME);
			LCD_movecursor(2,12+pass_counter);
			LCD_vSend_char(PASSWORD_SYMBOL);
			_delay_ms(100);
			pass_counter++;
			key_pressed = NOT_PRESSED;
		}
		/*compare passwords*/
		if ((ui8ComparePass(pass,Adminpass,PASS_SIZE)) == TRUE)//in case of right password
		{
			login_mode = ADMIN;//set the login mode to admin mode
			pass_tries_count=0;//clear the counter of wrong tries
			LCD_clearscreen();
			LCD_vSend_string("Right pass");
			LCD_movecursor(2,1);
			LCD_vSend_string("Admin mode");
			_delay_ms(500);
			LED_vTurnOn(ADMIN_LED_PORT,ADMIN_LED_PIN);//turn on the led of admin
			timer0_initializeCTC();
			LCD_clearscreen();
		}
		else//in case of wrong password
		{
			pass_tries_count++;
			login_mode = NO_MODE;
			LCD_clearscreen();
			LCD_vSend_string("Wrong Pass");
			LCD_movecursor(2,1);
			LCD_vSend_string("Tries left:");
			LCD_vSend_char(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);
			_delay_ms(1000);
			LCD_clearscreen();
			if (pass_tries_count>=TRIES_ALLOWED)
			{
				LOGIN_BLOCKED =TRUE;
				block_mode_flag = TRUE;
				break;//break the loop of admin login #while(login_mode!=ADMIN)
			}
		}
	}
}
void GistLogin(void)
{
	while(login_mode != GUEST)
	{
		key_pressed = NOT_PRESSED;//return the variable that holds the pressed key from keypad to its initial value
		LCD_clearscreen();
		LCD_vSend_string("Guest mode");
		LCD_movecursor(2,1);
		LCD_vSend_string("Enter pass:");
		_delay_ms(200);
		pass_counter=0;
		while(pass_counter<PASS_SIZE)
		{
			while (key_pressed == NOT_PRESSED)//repeat till the user press any key
			{
				key_pressed = keypad_u8check_press();//if the user pressed any button in keypad save the value in key_pressed
			}
			pass[pass_counter]=key_pressed-ASCII_ZERO;//add the pressed key to the password string
			LCD_vSend_char(key_pressed);//print the entered character
			_delay_ms(CHARACTER_PREVIEW_TIME);
			LCD_movecursor(2,12+pass_counter);//return the cursor to the location of the previous character to replace it with the password sign
			LCD_vSend_char(PASSWORD_SYMBOL); // to display (Password sign *)
			_delay_ms(100);
			pass_counter++;//increase the password counter that count the characters of the pass
			key_pressed = NOT_PRESSED;//return the variable that holds the pressed key from keypad to its initial value
		}

		/*compare passwords*/
		if (ui8ComparePass(pass,Gestpass,PASS_SIZE)==TRUE)//in case of right password
		{
			login_mode = GUEST;
			pass_tries_count=0;//clear the counter of wrong tries
			LCD_clearscreen();
			LCD_vSend_string("Right pass");
			LCD_movecursor(2,1);
			LCD_vSend_string("Guest mode");
			_delay_ms(500);
			LED_vTurnOn(GUEST_LED_PORT,GUEST_LED_PIN);//turn the led of gust mode that is connected to the master micro controller on
			timer0_initializeCTC();//start the counter of the session
			LCD_clearscreen();
		}
		else//in case of wrong password
		{
			pass_tries_count++;//increase the number of wrong tries to block login if it exceeds the allowed tries
			login_mode = NO_MODE;//set the mode as not logged in
			LCD_clearscreen();
			LCD_vSend_string("Wrong pass");
			LCD_movecursor(2,1);
			LCD_vSend_string("Tries left:");
			LCD_vSend_char(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);//print the number of tries left before block mode to be activated
			_delay_ms(1000);
			LCD_clearscreen();
			if (pass_tries_count>=TRIES_ALLOWED)//if the condition of the block mode is true
			{
				LOGIN_BLOCKED=TRUE;//write  TRUE to the the block mode
				block_mode_flag = TRUE;//turn on block mode
				break;//breaks the loop of insert guest password #while(login_mode != GUEST)
			}//The End of if that check if the number of tries exceeds the maximum tries allowed
		}//The End of the case of wrong password
	}//The End of loop of guest login

}

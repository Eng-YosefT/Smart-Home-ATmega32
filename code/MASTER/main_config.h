/**************************************************/
/*Desc   : main CONFIGRITON file for Master 	  */
/*Author : Youssef Taha Moawad		              */
/*Date   : 16 sep 2023                            */
/*Version: 1.0V                                   */
/**************************************************/

#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_
#include "STD_Types.h"

/*********************************** Passwords ***********************************/
#define SITPASS				TRUE			  //     OR  FALSE
#define ADMIN_PASS	   		{0,0,0,0}
#define GEST_PASS 			{1,1,1,1}
/*********************************************************************************/

#define NOT_STORED   0xFF
#define NOT_SELECTED 0xFF

#define BLOCK_MODE_TIME		  	20000
#define CHARACTER_PREVIEW_TIME (uint16)300
#define DEGREES_SYMBOL		   (uint8)0xDF

/*********************************** PIN Configuration ***********************************/
#define PASS_SIZE       (uint8)4
#define TRIES_ALLOWED   (uint8)3
#define PASSWORD_SYMBOL (uint8)'*'
#define ASCII_ZERO      (uint8)'0'

#define PASS_NOT_SET 	 0
#define PASS_SET    	 1

/*****************************************************************************************/

/************************************   Login configurations *****************************/
#define NO_MODE (uint8)0
#define ADMIN   (uint8)1
#define GUEST   (uint8)2
/*****************************************************************************************/

/************************************   Logic values *************************************/
#define FALSE   (uint8)0
#define TRUE    (uint8)1
/*****************************************************************************************/

#define CHECK_ADMIN_MODE        (uint8)'0'
#define CHECK_GUEST_MODE        (uint8)'1'

#define SELECT_PASS_RET     	(uint8)'0'
#define SELECT_CHNG_ADMIN_PASS	(uint8)'1'
#define SELECT_CHNG_GUEST_PASS	(uint8)'2'

#define SELECT_LIGHT_CONTROL    (uint8)'1'
#define SELECT_PASSWORD			(uint8)'2'
#define SELECT_AIR_CONDITIONING (uint8)'3'
#define SELECT_TV               (uint8)'4'


#define SELECT_ROOM1            (uint8)'1'
#define SELECT_ROOM2            (uint8)'2'
#define SELECT_ROOM3            (uint8)'3'
#define SELECT_ROOM4            (uint8)'4'


#define SELECT_SET_TEMPERATURE  (uint8)'1'
#define SELECT_AIR_COND_CTRL    (uint8)'2'
#define SELECT_AIR_COND_RET     (uint8)'0'

/****************************   number of ticks to run timeout ***************************/
#define ADMIN_TIMEOUT (uint16)3000
#define GUEST_TIMEOUT (uint16)2000
/*****************************************************************************************/

/****************************   Show menu codes  *****************************************/
#define MAIN_MENU            (uint8)1
#define LIGHT_CONTROL_MENU	 (uint8)2
#define ROOM1_MENU           (uint8)3
#define ROOM2_MENU           (uint8)4
#define ROOM3_MENU           (uint8)5
#define ROOM4_MENU           (uint8)6
#define TV_MENU              (uint8)7
#define AIRCONDITIONING_MENU (uint8)8
#define AIRCOND_CTRL_MENU    (uint8)9
#define TEMPERATURE_MENU     (uint8)10
#define PASSWORD_MENU 		 (uint8)11
#define CHNG_ADMIN_PASS_MENU (uint8)12
#define CHNG_GUEST_PASS_MENU (uint8)13
/*****************************************************************************************/
// Function Prototypes
void initializeSystem(void);
void printWelcomeScreen(void);
void setAdminPassword(void);
void setGestPassword(void);
void AdiminLogin(void);
void GistLogin(void);

#endif /* MAIN_CONFIG_H_ */

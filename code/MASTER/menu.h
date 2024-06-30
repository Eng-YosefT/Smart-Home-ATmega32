/**************************************************/
/*Desc   : menu HEDER file for Master 			  */
/*Author : Youssef Taha Moawad		              */
/*Date   : 16 sep 2023                            */
/*Version: 1.0V                                   */
/**************************************************/
#ifndef MENU_H_
#define MENU_H_

#include "main_config.h"
#include "STD_MESSAGES.h"
#include "STD_Types.h"
#include "keypad_driver.h"
#include "SPI.h"
#include "LCD.h"


uint8 ui8ComparePass(const uint8* pass1,const uint8* pass2,const uint8 size);


void vMenuOption(const uint8 u8SelectedRoom,const uint8 u8LoginMode);


uint8 u8GetKeyPressed(const uint8 u8LoginMode);

#endif /* MENU_H_ */

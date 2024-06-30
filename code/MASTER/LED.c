/**************************************************/
/*Desc   : LED file for Master mivcrocontroller   */
/*Author : Youssef Taha Moawad		              */
/*Date   : 16 sep 2023                            */
/*Version: 1.0V                                   */
/**************************************************/

#include "LED.h"
void LED_vInit(uint8 portname,uint8 pinnumber)
{
	DIO_vsetPINDir(portname,pinnumber,1);
}
void LED_vTurnOn(uint8 portname,uint8 pinnumber)
{
	DIO_write(portname,pinnumber,1);
}
void LED_vTurnOff(uint8 portname,uint8 pinnumber)
{
	DIO_write(portname,pinnumber,0);
}
void LED_vToggle(uint8 portname,uint8 pinnumber)
{
	DIO_toggle(portname,pinnumber);
}
uint8 LED_u8ReadStatus(uint8 portname,uint8 pinnumber)
{
	return DIO_u8read(portname,pinnumber);
}

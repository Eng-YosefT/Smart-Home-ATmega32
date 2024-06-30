/**************************************************/
/*Desc   : DIO heder file slave mivcrocontroller  */
/*Author : Youssef Taha Moawad		              */
/*Date   : 16 sep 2023                            */
/*Version: 1.0V                                   */
/**************************************************/
#ifndef DIO_H_
#define DIO_H_
#define F_CPU 8000000ul
#include <util/delay.h>
#include "DIO_Slave_cfg.h"
#include "STD_Types.h"


void DIO_vsetPINDir(uint8 portname,uint8 pinnumber,uint8 direction);


void DIO_write(uint8 portname,uint8 pinnumber,uint8 outputvalue);

uint8 DIO_u8read(uint8 portname,uint8 pinnumber);


void DIO_toggle(uint8 portname,uint8 pinnumber);


void DIO_write_port(uint8 portname,uint8 portvalue);


void clear_high_nibble(uint8 portname) ;


void dio_write_highnibble(uint8 portname,uint8 value);


void DIO_vconnectpullup(uint8 portname ,uint8 pinnumber, uint8 connect_pullup);

#endif /* DIO_H_ */

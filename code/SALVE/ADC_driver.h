/**************************************************/
/*Desc   : ADC heder file slave mivcrocontroller  */
/*Author : Youssef Taha Moawad		              */
/*Date   : 16 sep 2023                            */
/*Version: 1.0V                                   */
/**************************************************/
#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_
#include "STD_Types.h"


void ADC_vinit(void);


uint16 ADC_u16Read(void);

#endif /* ADC_DRIVER_H_ */

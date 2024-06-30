# Smart-Home-ATmega32
ITI Embedded Systems Diploma project. ATmega32 controlled system with user interface (LCD/keypad). Manages lighting (LEDs), climate (LM35 sensor), and security (user types). Built with Proteus and coded in Eclipse.

#Smart Home Automation System - ITI Diploma Project

This repository contains the code and documentation for a smart home automation system developed as part of the Embedded Systems Diploma program at the Information Technology Institute (ITI).

#Project Overview:

The system utilizes two ATmega32 microcontrollers (MASTER and SLAVE) to control lighting, temperature, and other functionalities within a simulated home environment. The system features a user-friendly interface with LCD display and keypad for user interaction, and includes advanced features such as:
Lighting Control: Control individual room lighting with LEDs.
Climate Control: Monitor room temperature using LM35 sensor and control air conditioning system.
User Management: Implement GUEST and ADMIN roles with password authentication.
Secure Communication: Use SPI protocol for data exchange between MASTER and SLAVE.

#Technical Details:

##Hardware:

ATmega32 Microcontrollers (Master & Slave)
LEDs for lighting
LM35 temperature sensor
LM016L LCD Display
4x4 Keypad
ADC module

##Software:

AVR-GCC Compiler
Eclipse IDE
C programming language
SPI communication protocol
Drivers for components (LED, ADC, SPI, Timer)
Menu system with user roles and password management

#Project Structure:

##Master Microcontroller:

main.c: Main program code for MASTER
main_config.h: Configuration file for MASTER
LCD.h, LCD.c: LCD driver files
keypad_driver.h, keypad_driver.c: Keypad driver files
SPI.h, SPI.c: SPI communication driver files
LED.h, LED.c: LED driver files
timer_driver.h, timer_driver.c: Timer driver files
menu.h, menu.c: Menu system files
DIO_config_master.h: DIO configuration file for MASTER
DIO.h, DIO.c: DIO driver files

##Slave Microcontroller:

main.c: Main program code for SLAVE
APP_slave_Macros.h: Macro definitions for SLAVE
LED.h, LED.c: LED driver files
ADC_driver.h, ADC_driver.c: ADC driver files
timer_driver.h, timer_driver.c: Timer driver files
SPI.h, SPI.c: SPI communication driver files
DIO.h, DIO.c: DIO driver files
DIO_Slave_cfg.h: DIO configuration file for SLAVE

#Contribution:

This project was a collaborative effort by a team of five engineers. I acted as the team leader, coordinating efforts and ensuring timely completion of tasks. We were responsible for various aspects of the project, including:
Hardware Selection and Integration: Choosing and connecting the appropriate components.
Microcontroller Programming: Writing the firmware for both MASTER and SLAVE.
User Interface Design: Creating the menu system and user interaction logic.
Code Development and Testing: Writing drivers and testing the functionalities.


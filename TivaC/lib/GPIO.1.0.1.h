/*
 *	File			:	GPIO.1.0.1.h
 *	Date created	:	08/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		:	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Version			:	1.0.1
 *	Description		:	Library of GPIO
 */
/**************************************************************************************************
 *	PRE-DEIFINITIONs
 *************************************************************************************************/
#ifndef GPIO_1_0_1_H_
#define GPIO_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

/* Producing Library */
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

/* My Library */
#include "LAUNCHPAD.1.0.1.h"

/* This project */


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Port (15 ports) */
#define		GPIO_PORT_A				GPIO_PORTA_BASE
#define		GPIO_PORT_B				GPIO_PORTB_BASE
#define		GPIO_PORT_C				GPIO_PORTC_BASE
#define		GPIO_PORT_D				GPIO_PORTD_BASE
#define		GPIO_PORT_E				GPIO_PORTE_BASE
#define		GPIO_PORT_F				GPIO_PORTF_BASE
#define		GPIO_PORT_G				GPIO_PORTG_BASE
#define		GPIO_PORT_H				GPIO_PORTH_BASE
#define		GPIO_PORT_J				GPIO_PORTJ_BASE
#define		GPIO_PORT_K				GPIO_PORTK_BASE
#define		GPIO_PORT_L				GPIO_PORTL_BASE
#define		GPIO_PORT_M				GPIO_PORTM_BASE
#define		GPIO_PORT_N				GPIO_PORTN_BASE
#define		GPIO_PORT_P				GPIO_PORTP_BASE
#define		GPIO_PORT_Q				GPIO_PORTQ_BASE

//-------------------------------------------------------------------------------------------------
/* Input */
#define		GPIO_IN_PULL_UP			GPIO_PIN_TYPE_STD_WPU
#define		GPIO_IN_PULL_DOWN		GPIO_PIN_TYPE_STD_WPD

//-------------------------------------------------------------------------------------------------
/* Interrupt */
#define		GPIO_IN_DETECT_FALL		GPIO_FALLING_EDGE
#define		GPIO_IN_DETECT_RISE		GPIO_RISING_EDGE
#define		GPIO_IN_DETECT_BOTH		GPIO_BOTH_EDGES
#define		GPIO_IN_DETECT_LOW		GPIO_LOW_LEVEL
#define		GPIO_IN_DETECT_HIGH		GPIO_HIGH_LEVEL


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Setup */
void
gpioOutputSetup (uint32_t GPIO_PORT_, uint8_t GPIO_PIN_);
void
gpioInputSetup	(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_, uint32_t GPIO_IN_PULL_);
void
gpioEnablePort	(uint32_t GPIO_PORT_);

//-------------------------------------------------------------------------------------------------
/* Interrupt */
void
gpioIntSetup	(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_, uint32_t GPIO_IN_DETECT_,
																		void (*GPIO_ISR)(void));
void
gpioIntExit		(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_);

//-------------------------------------------------------------------------------------------------
/* Basic operation */
void
gpioHigh		(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_);
void
gpioLow			(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_);
void
gpioToggle		(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_);
int32_t
gpioRead		(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_);

//-------------------------------------------------------------------------------------------------
/* LED */
void
gpioLEDSetup	(uint8_t varLED);
void
gpioLEDState	(uint8_t varLED, uint8_t state);

//-------------------------------------------------------------------------------------------------
/* Button */
void
gpioBtnSetup	(uint8_t varBtn);
void
gpioBtnIntSetup	(uint8_t varBtn, void (*GPIO_BTN_ISR)(void));
uint8_t
gpioBtnRead		(uint8_t varBtn);


/**************************************************************************************************
 *	END OF GPIO.1.0.1.h
 *************************************************************************************************/
#endif /* GPIO_1_0_1_H_ */

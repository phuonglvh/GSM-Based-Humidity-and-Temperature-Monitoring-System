/*
 *	File			:	UART.1.0.1.h
 *	Date created	:	10/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	1.0.1
 *	Description		:	Library of UART
 */
/**************************************************************************************************
 *	PRE-DEIFINITIONs
 *************************************************************************************************/
#ifndef UART_1_0_1_H_
#define UART_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "stdarg.h"

/* Producing Library */
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"

#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

#include "utils/uartstdio.h"

/* My Library */
#include "LAUNCHPAD.1.0.1.h"
#include "CLK.1.0.1.h"
#include "GPIO.1.0.1.h"

/* This project */


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Module */
#define 	UART0			UART0_BASE
#define		UART1			UART1_BASE
#define		UART2			UART2_BASE
#define		UART3			UART3_BASE
#define		UART4			UART4_BASE
#define		UART5			UART5_BASE
#define		UART6			UART6_BASE
#define		UART7			UART7_BASE

//-------------------------------------------------------------------------------------------------
/* Interrupt */
#define		UART_INT_OFF	0


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Setup */
void
uartSetup			(uint32_t ui32ClkFreq, uint32_t UART, uint32_t ui32Baud, uint32_t UART_INT_);
void
uartEnableModule	(uint32_t UART);
void
uartInitStr			(uint32_t UART);

/* Send */
void
uartSendChar		(uint32_t UART, char varSource);
void
uartSendStr			(uint32_t UART, char strSource[]);
void
uartSendArr         (uint32_t UART, uint8_t arr[], uint16_t len);
void
uartSendNumber		(uint32_t UART, uint32_t ui32Number, bool isNewLine);
void
uartSendBinary		(uint32_t UART, uint32_t ui32Binary, bool isNewLine);
void
uartSendHex			(uint32_t UART, uint32_t ui32Hex, bool isNewLine);
#define	uartPrintf	UARTprintf

/* Get */
uint8_t
uartGetChar			(uint32_t UART);
void
uartGetStr			(uint32_t UART, uint8_t strDest[]);
void
uartGetStrNLCR		(uint32_t UART, uint8_t strDest[]);

/* Interrupt */
void
uartISRExit			(uint32_t UART);


/**************************************************************************************************
 *	END OF UART.1.0.1.h
 *************************************************************************************************/
#endif /* UART_1_0_1_H_ */

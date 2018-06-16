/*
 *	File			:	TIMER.1.0.1.h
 *	Date created	:	22/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	1.0.1
 *	Description		:	Library of TIMER
 */
/**************************************************************************************************
 *	PRE-DEIFINITIONs
 *************************************************************************************************/
#ifndef TIMER_1_0_1_H_
#define TIMER_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
 /* Standard Library */
#include <stdint.h>
#include <stdbool.h>
 
 /* Producing Library */
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"

#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
 
 /* My Library */
 
 /* This project */


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Module */
#define	TIMER0				TIMER0_BASE
#define	TIMER1				TIMER1_BASE
#define	TIMER2				TIMER2_BASE
#define	TIMER3				TIMER3_BASE
#define	TIMER4				TIMER4_BASE
#define	TIMER5				TIMER5_BASE
#define	TIMER6				TIMER6_BASE
#define	TIMER7				TIMER7_BASE

//-------------------------------------------------------------------------------------------------
/* Clock source */
#define	TIMER_CLK_PIOSC		TIMER_CLOCK_PIOSC
#define	TIMER_CLK_SYSTEM	TIMER_CLOCK_SYSTEM

//-------------------------------------------------------------------------------------------------
/* Setup */
void
timerSetup		(uint32_t TIMER, uint32_t TIMER_, uint32_t TIMER_CFG_, bool isInt,
															uint32_t varPreScl, uint32_t varTmo);
void
timerStart      (uint32_t TIMER, uint32_t TIMER_);
void
timerStop		(uint32_t TIMER, uint32_t TIMER_);
void
timerIntExit	(uint32_t TIMER, uint32_t TIMER_);

//-------------------------------------------------------------------------------------------------
/* Timeout */
void
timerTimeoutSet	(uint32_t TIMER, uint32_t TIMER_, uint32_t varLoad);
uint32_t
timerTimeoutGet	(uint32_t TIMER, uint32_t TIMER_);

//-------------------------------------------------------------------------------------------------
/* Delay */
void
timerDelay		(uint32_t varTimerTmo);	


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Enable Timer and Timer interrupt */
static	void
timerEnable		(uint32_t TIMER);
static	void
intEnableTimer	(uint32_t TIMER, uint32_t TIMER_);


/**************************************************************************************************
 *	END OF TIMER.1.0.1.h
 *************************************************************************************************/
#endif /* TIMER_1_0_1_H_ */

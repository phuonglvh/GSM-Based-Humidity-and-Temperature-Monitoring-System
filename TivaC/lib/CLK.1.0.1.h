/*
 *	File		:	CLK.1.0.1.h
 *	Date		:	2017/1/12
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Header of Clock
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

/* Producer */
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"

/* My */
#include "LAUNCHPAD.1.0.1.h"

/* This project */


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Frequency of Clock */
extern	uint32_t		ui32ClkFreq;

//-------------------------------------------------------------------------------------------------
/* Clock Sources */
#define	CLK_SRC_MAIN				SYSCTL_OSC_MAIN		// Main oscillator, 25MHz
#define	CLK_SRC_PIOSC				SYSCTL_OSC_INT		// Precise Internal Oscillator, 16MHz
#define	CLK_SRC_PIOSC4				SYSCTL_OSC_INT4		// Precise Internal Oscillator, 4MHz
#define	CLK_SRC_INT30				SYSCTL_OSC_INT30	// Internal, 30 KHz
#define	CLK_SRC_EXT32				SYSCTL_OSC_EXT32	// External, 32 KHz

//-------------------------------------------------------------------------------------------------
/* Use PLL */
#define	CLK_PLL_ON					SYSCTL_USE_PLL		// Using PLL output as system clock
#define	CLK_PLL_OFF					SYSCTL_USE_OSC		// Using Oscillator as system clock

//-------------------------------------------------------------------------------------------------
/* Clock freqency */
#define	CLK_FREQ_1MHZ				1000000
#define	CLK_FREQ_8MHZ				8000000
#define	CLK_FREQ_16MHZ				16000000
#define	CLK_FREQ_25MHZ				25000000
#define	CLK_FREQ_120MHZ				120000000

//-------------------------------------------------------------------------------------------------
/* NOP */
#define	NOP			__nop()

//-------------------------------------------------------------------------------------------------
/* Setup */
void
clkSetup			(uint32_t CLK_SRC_, uint32_t CLK_PLL_, uint32_t CLK_FREQ_);

//-------------------------------------------------------------------------------------------------
/* Delay */
void
clkDelayCycle		(uint32_t ui32Cycle);
void
clkDelayUs			(uint32_t ui32Us);
void
clkDelayMs			(uint32_t ui32Ms);

void
clkDelay1Us			(void);
void
clkDelay10Us		(void);
void
clkDelay100Us		(void);

void
clkDelay10Cycle		(void);
void
clkDelay100Cycle	(void);
void
clkDelay1000Cycle	(void);


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/*
 *	File			:	LAUNCHPAD.1.0.1.c
 *	Date created	:	08/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	1.0.1
 *	Description		:	Hardware of The Connected LaunchPad EK-TM4C1294XL
 */
/**************************************************************************************************
 *	INCLUDE
 *************************************************************************************************/
#include "LAUNCHPAD.1.0.1.h"
#include "CLK.1.0.1.h"
#include "GPIO.1.0.1.h"
#include "UART.1.0.1.h"


/**************************************************************************************************
 *	PRIVATE
 *************************************************************************************************/
/* Bit access */
static	uint32_t	arrBit[8] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080 };

//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	FUNCTION
 *************************************************************************************************/
/*
 *	Input		:	reg: Register
 *					bit: Bit in this register
 *	Output		:	None
 *	Description	:	Clear bit of register
 */
void	cbi(uint32_t reg, uint8_t bit)
{
	reg &= ~arrBit[bit];
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	reg: Register
 *					bit: Bit in this register
 *	Output		:	None
 *	Description	:	Set bit of register
 */
void	sbi(uint32_t reg, uint8_t bit)
{
	reg |= arrBit[bit];
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	isUseLED	: Check whether using 4 LEDs
 *					isUsedUART	: Check whether using UART, baud = 115200
 *	Output		:	None
 *	Description	:	Setup basic components
 */
void	fastSetup(bool isUseLED, bool isUsedUART)
{
	/* Clock */
	clkSetup(CLK_SRC_MAIN, CLK_PLL_ON, CLK_FREQ_120MHZ);

	/* GPIO LED */
	if(isUseLED)
	{
		gpioLEDSetup(1);
		gpioLEDSetup(2);
		gpioLEDSetup(3);
		gpioLEDSetup(4);
	}

	/* UART */
	if(isUsedUART)
	{
		uartSetup(ui32ClkFreq, UART_ICDI, 115200, UART_INT_OFF);
		uartInitStr(UART_ICDI);
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */


/**************************************************************************************************
 *	END OF LAUNCHPAD.1.0.1.c
 *************************************************************************************************/

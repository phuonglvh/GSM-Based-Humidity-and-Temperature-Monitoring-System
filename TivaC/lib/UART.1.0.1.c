/*
 *	File			:	UART.1.0.1.c
 *	Date created	:	10/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	1.0.1
 *	Description		:	Library of UART
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */

/* Producing Library */

/* My Library */
#include "UART.1.0.1.h"

/* This project */


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
 
 
 /**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
#define	PORT(x)				(GPIO_PORT_##x)		// Get GPIO port name
#define	INT(x)				(INT_##x)			// Get interrupt name

void	uartSetup(uint32_t ui32ClkFreq, uint32_t UART, uint32_t ui32Baud, uint32_t UART_INT_)
{
	/* Declare */
	uint32_t ui32GPIOPort, varGPIOMuxRX, varGPIOMuxTX, varGPIOPinRX, varGPIOPinTX;

	/* Indicate module */
	switch (UART)
	{
		case UART0:
			ui32GPIOPort = PORT(A);
			varGPIOMuxRX = GPIO_PA0_U0RX; varGPIOMuxTX = GPIO_PA1_U0TX;
			varGPIOPinRX = GPIO_PIN_0	; varGPIOPinTX = GPIO_PIN_1;
			break;
		case UART1:
			ui32GPIOPort = PORT(B);
			varGPIOMuxRX = GPIO_PB0_U1RX; varGPIOMuxTX = GPIO_PB1_U1TX;
			varGPIOPinRX = GPIO_PIN_0	; varGPIOPinTX = GPIO_PIN_1;
			break;
		case UART2:
			ui32GPIOPort = PORT(A);
			varGPIOMuxRX = GPIO_PA6_U2RX; varGPIOMuxTX = GPIO_PA7_U2TX;
			varGPIOPinRX = GPIO_PIN_6	; varGPIOPinTX = GPIO_PIN_7;
			break;
		case UART3:
			ui32GPIOPort = PORT(A);
			varGPIOMuxRX = GPIO_PA4_U3RX; varGPIOMuxTX = GPIO_PA5_U3TX;
			varGPIOPinRX = GPIO_PIN_4	; varGPIOPinTX = GPIO_PIN_5;
			break;
		case UART4:
			ui32GPIOPort = PORT(A);
			varGPIOMuxRX = GPIO_PA2_U4RX; varGPIOMuxTX = GPIO_PA3_U4TX;
			varGPIOPinRX = GPIO_PIN_2	; varGPIOPinTX = GPIO_PIN_3;
			break;
		case UART5:
			ui32GPIOPort = PORT(C);
			varGPIOMuxRX = GPIO_PC6_U5RX; varGPIOMuxTX = GPIO_PC7_U5TX;
			varGPIOPinRX = GPIO_PIN_6	; varGPIOPinTX = GPIO_PIN_7;
			break;
		case UART6:
			ui32GPIOPort = PORT(P);
			varGPIOMuxRX = GPIO_PP0_U6RX; varGPIOMuxTX = GPIO_PP1_U6TX;
			varGPIOPinRX = GPIO_PIN_0	; varGPIOPinTX = GPIO_PIN_1;
			break;
		case UART7:
			ui32GPIOPort = PORT(C);
			varGPIOMuxRX = GPIO_PC4_U7RX; varGPIOMuxTX = GPIO_PC5_U7TX;
			varGPIOPinRX = GPIO_PIN_4	; varGPIOPinTX = GPIO_PIN_5;
			break;
	}

	/* Enable UART and config GPIO pin */
	uartEnableModule(UART);					// Enable UART module
    gpioEnablePort(ui32GPIOPort);			// Enable GPIO Port
    GPIOPinConfigure(varGPIOMuxRX);			// Mux pin RX
    GPIOPinConfigure(varGPIOMuxTX);			// Mux pin TX
    GPIOPinTypeUART(ui32GPIOPort, varGPIOPinRX | varGPIOPinTX);
    										// Configure pin for UART
    /* Config UART */
    UARTConfigSetExpClk(UART, ui32ClkFreq, ui32Baud,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	
	/* Interrupt */
    if(UART_INT_)
    {
		IntMasterEnable();
		switch (UART)
		{
			case UART0: IntEnable(INT(UART0));	break;
			case UART1: IntEnable(INT(UART1)); 	break;
			case UART2: IntEnable(INT(UART2)); 	break;
			case UART3: IntEnable(INT(UART3)); 	break;
			case UART4: IntEnable(INT(UART4)); 	break;
			case UART5: IntEnable(INT(UART5)); 	break;
			case UART6: IntEnable(INT(UART6)); 	break;
			case UART7: IntEnable(INT(UART7)); 	break;
		}
		UARTIntEnable(UART, UART_INT_);
    }
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
#define	PERIPH(x)		(SYSCTL_PERIPH_##x)

void	uartEnableModule(uint32_t UART)
{
	/* Declare */
	uint32_t ui32Periph = 0;

	/* Indicate peripheral */
	switch (UART)
	{
		case UART0: ui32Periph = PERIPH(UART0); break;
		case UART1: ui32Periph = PERIPH(UART1); break;
		case UART2: ui32Periph = PERIPH(UART2); break;
		case UART3: ui32Periph = PERIPH(UART3); break;
		case UART4: ui32Periph = PERIPH(UART4); break;
		case UART5: ui32Periph = PERIPH(UART5); break;
		case UART6: ui32Periph = PERIPH(UART6); break;
		case UART7: ui32Periph = PERIPH(UART7); break;
	}

	/* Enable peripheral */
	SysCtlPeripheralEnable(ui32Periph);

	/* Wait for peripheral ready */
	while(!SysCtlPeripheralReady(ui32Periph));
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:	Send an initialized string
 *	Input	:	None
 *	Output	:	None
 */
void	uartInitStr(uint32_t UART)
{
	uartSendStr(UART, "\n\n------------------------\n");
	uartSendStr(UART,     "| KIT  : EK-TM4C1294XL |\n");
	uartSendStr(UART,     "| Chip : TM4C1294NCPDT |\n");
	uartSendStr(UART,     "------------------------\n");
	
	uartSendStr(UART, "Clk = ");
	uartSendNumber(UART, ui32ClkFreq, 1);
	uartSendChar(UART, 10);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void	uartSendChar(uint32_t UART, char varSource)
{
	while(HWREG(UART + UART_O_FR) & UART_FR_TXFF);
	HWREG(UART + UART_O_DR) = varSource;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void	uartSendStr(uint32_t UART, char strSource[])
{
	char varTmpCount = 0;
	while(*(strSource + varTmpCount) != '\0')
	{
		while(HWREG(UART + UART_O_FR) & UART_FR_TXFF);
		HWREG(UART + UART_O_DR) = *(strSource + varTmpCount++);
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *  Purpose :
 *  Input   :
 *  Output  :   None
 */
void    uartSendArr(uint32_t UART, uint8_t arr[], uint16_t len)
{
    uint8_t i;
    for(i = 0; i < len; i++)
    {
        while(HWREG(UART + UART_O_FR) & UART_FR_TXFF);
        HWREG(UART + UART_O_DR) = arr[i];
    }
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:	
 *	Input	:	
 *	Output	:	
 */
void	uartSendNumber(uint32_t UART, uint32_t ui32Number, bool isNewLine)
{
	char strBuff[11];
	sprintf(strBuff, "%u", ui32Number);
	uartSendStr(UART, strBuff);
	if(isNewLine)	uartSendChar(UART, 10);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void	uartSendBinary(uint32_t UART, uint32_t ui32Binary, bool isNewLine)
{
	uint8_t i;
	for(i = 0; i < 32; i++)
	{
		if(ui32Binary & 0x80000000) uartSendChar(UART, '1');
		else						uartSendChar(UART, '0');
		ui32Binary <<= 1;
		if(i % 8 == 7 & i != 31)
		{
			uartSendStr(UART, " . ");
			continue;
		}
		if(i % 4 == 3)				uartSendChar(UART, ' ');
	}
	if(isNewLine)	uartSendChar(UART, 10);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void	uartSendHex(uint32_t UART, uint32_t ui32Hex, bool isNewLine)
{
	char strBuff[9];
	sprintf(strBuff, "%x", ui32Hex);
	uartSendStr(UART, strBuff);
	if(isNewLine)	uartSendChar(UART, 10);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
uint8_t	uartGetChar (uint32_t UART)
{
	while(HWREG(UART + UART_O_FR) & UART_FR_RXFE)
	{
	}
    return(HWREG(UART + UART_O_DR));
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void	uartGetStr (uint32_t UART, uint8_t strDest[])
{
	uint8_t i = 0;
	do
	{
		*(strDest + i) = uartGetChar(UART);
	} while(*(strDest + i++) != '\0');
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void	uartGetStrNLCR(uint32_t UART, uint8_t strDest[])
{
	uint8_t i = 0;
	do
	{
		*(strDest + i) = (uint8_t)UARTCharGet(UART);
	} while(*(strDest + i - 1) != '\r' && *(strDest + i++) != '\n');
	*(strDest + ++i) = '\0';
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void	uartISRExit(uint32_t UART)
{
	uint32_t 	varStatus;
	varStatus = UARTIntStatus(UART, true);	// Get the interrrupt status
	UARTIntClear(UART, varStatus);			// Clear the asserted interrupts
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF UART.1.0.1.c
 *************************************************************************************************/

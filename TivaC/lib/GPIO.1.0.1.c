/*
 *	File			:	GPIO.1.0.1.c
 *	Date created	:	08/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		:	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Version			:	1.0.1
 *	Description		:	Library of GPIO
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */

/* Producing Library */

/* My Library */
#include "GPIO.1.0.1.h"

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
 *	Function:	gpioOutputSetup
 *	Purpose	:	Setup GPIO output
 *	Input	:	GPIO_PORT_: Which port?
 *				GPIO_PIN_: Which pins of port?
 *	Output	:	None
 */
void
gpioOutputSetup (uint32_t GPIO_PORT_, uint8_t GPIO_PIN_)
{
	/* Check and enable peripheral */
	gpioEnablePort(GPIO_PORT_);

	/* Config as GPIO output */
	GPIOPinTypeGPIOOutput(GPIO_PORT_, GPIO_PIN_);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioInputSetup
 *	Purpose	:	Setup GPIO input
 *	Input	:	GPIO_PORT_: Which port?
 *				GPIO_PIN_: Which pins of port?
 *	Output	:	None
 */
void
gpioInputSetup	(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_, uint32_t GPIO_IN_PULL_)
{
	/* Check and enable peripheral */
	gpioEnablePort(GPIO_PORT_);

	/* Config GPIO input and pull resistor */
	GPIOPinTypeGPIOInput(GPIO_PORT_, GPIO_PIN_);
	GPIOPadConfigSet(GPIO_PORT_, GPIO_PIN_, GPIO_STRENGTH_8MA, GPIO_IN_PULL_);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioCheckPresentPort
 *	Purpose	:	Check and enable GPIO port
 *	Input	:	GPIO_PORT_: Which port?
 *	Output	:	None
 */
void
gpioEnablePort(uint32_t GPIO_PORT_)
{
	/* Declare */
	uint32_t varPeriph = 0;

	/* Indicate port */
	switch (GPIO_PORT_)
	{
		case GPIO_PORT_A: varPeriph = SYSCTL_PERIPH_GPIOA; break;
		case GPIO_PORT_B: varPeriph = SYSCTL_PERIPH_GPIOB; break;
		case GPIO_PORT_C: varPeriph = SYSCTL_PERIPH_GPIOC; break;
		case GPIO_PORT_D: varPeriph = SYSCTL_PERIPH_GPIOD; break;
		case GPIO_PORT_E: varPeriph = SYSCTL_PERIPH_GPIOE; break;
		case GPIO_PORT_F: varPeriph = SYSCTL_PERIPH_GPIOF; break;
		case GPIO_PORT_G: varPeriph = SYSCTL_PERIPH_GPIOG; break;
		case GPIO_PORT_H: varPeriph = SYSCTL_PERIPH_GPIOH; break;
		case GPIO_PORT_J: varPeriph = SYSCTL_PERIPH_GPIOJ; break;
		case GPIO_PORT_K: varPeriph = SYSCTL_PERIPH_GPIOK; break;
		case GPIO_PORT_L: varPeriph = SYSCTL_PERIPH_GPIOL; break;
		case GPIO_PORT_M: varPeriph = SYSCTL_PERIPH_GPIOM; break;
		case GPIO_PORT_N: varPeriph = SYSCTL_PERIPH_GPION; break;
		case GPIO_PORT_P: varPeriph = SYSCTL_PERIPH_GPIOP; break;
		case GPIO_PORT_Q: varPeriph = SYSCTL_PERIPH_GPIOQ; break;
	}

	/* Enable peripheral */
	SysCtlPeripheralEnable(varPeriph);

	/* Wait for peripheral ready */
	while(!SysCtlPeripheralReady(varPeriph));
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioIntSetup
 *	Purpose	:	Setup GPIO interrupt
 *	Input	:	GPIO_PORT_: Which port?
 *				GPIO_PIN_: Which pins of port?
 *				GPIO_IN_DETECT_: Which detect?
 *				pGPIO_ISR: pointer to ISR funtion (named GPIO_ISR)
 *	Output	:	None
 */
void
gpioIntSetup (uint32_t GPIO_PORT_, uint8_t GPIO_PIN_, uint32_t GPIO_IN_DETECT_, void (*GPIO_ISR)(void))
{
	/* Config GPIO */
	GPIOIntTypeSet(GPIO_PORT_, GPIO_PIN_, GPIO_IN_DETECT_);
	GPIOIntRegister(GPIO_PORT_, GPIO_ISR);
	GPIOIntEnable(GPIO_PORT_, GPIO_PIN_);

	/* Enable interrupt */
	switch (GPIO_PORT_)
	{
		case GPIO_PORT_A: IntEnable(INT_GPIOA);	break;
		case GPIO_PORT_B: IntEnable(INT_GPIOB);	break;
		case GPIO_PORT_C: IntEnable(INT_GPIOC);	break;
		case GPIO_PORT_D: IntEnable(INT_GPIOD);	break;
		case GPIO_PORT_E: IntEnable(INT_GPIOE);	break;
		case GPIO_PORT_F: IntEnable(INT_GPIOF);	break;
		case GPIO_PORT_G: IntEnable(INT_GPIOG);	break;
		case GPIO_PORT_H: IntEnable(INT_GPIOH);	break;
		case GPIO_PORT_J: IntEnable(INT_GPIOJ);	break;
		case GPIO_PORT_K: IntEnable(INT_GPIOK);	break;
		case GPIO_PORT_L: IntEnable(INT_GPIOL);	break;
		case GPIO_PORT_M: IntEnable(INT_GPIOM);	break;
		case GPIO_PORT_N: IntEnable(INT_GPION);	break;
	}

	/* Enable Master interrupt */
	IntMasterEnable();
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioIntExit
 *	Purpose	:	Exit from GPIO_ISR
 *	Input	:	GPIO_PORT_: Which port?
 *				GPIO_PIN_: Which pins of port?
 *	Output	:	None
 */
void
gpioIntExit (uint32_t GPIO_PORT_, uint8_t GPIO_PIN_)
{
	GPIOIntClear(GPIO_PORT_, GPIO_PIN_);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioHigh
 *	Purpose	:	Turn on GPIO output
 *	Input	:	GPIO_PORT_: Which port?
 *				GPIO_PIN_: Which pins of port?
 *	Output	:	None
 */
void	gpioHigh(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_)
{
	HWREG(GPIO_PORT_ + (GPIO_O_DATA + (GPIO_PIN_ << 2))) |= GPIO_PIN_;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioLow
 *	Purpose	:	Turn off GPIO output
 *	Input	:	GPIO_PORT_: Which port?
 *				GPIO_PIN_: Which pins of port?
 *	Output	:	None
 */
void	gpioLow(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_)
{
	HWREG(GPIO_PORT_ + (GPIO_O_DATA + (GPIO_PIN_ << 2))) &= ~GPIO_PIN_;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioToggle
 *	Purpose	:	Toggle level of GPIO output
 *	Input	:	GPIO_PORT_: Which port?
 *				GPIO_PIN_: Which pins of port?
 *	Output	:
 */
void	gpioToggle(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_)
{
	HWREG(GPIO_PORT_ + (GPIO_O_DATA + (GPIO_PIN_ << 2))) ^= GPIO_PIN_;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioRead
 *	Purpose	:	Read value of GPIO input
 *	Input   :	GPIO_PORT_: Which port?
 *				GPIO_PIN_: Which pins of port?
 *	Output	:	Value of specified pins
 */
int32_t	gpioRead(uint32_t GPIO_PORT_, uint8_t GPIO_PIN_)
{
	return (HWREG(GPIO_PORT_ + (GPIO_O_DATA + (GPIO_PIN_ << 2))));
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioLEDSetup
 *	Purpose	:	Setup LED as GPIO output
 *	Input		:	varLED: Number to indicate LED (1, 2, 3, 4)
 *	Output	:	None
 */
void	gpioLEDSetup(uint8_t varLED)
{
	/* Declare */
	uint32_t port, pin;
	
	/* Assign port and pin */
	switch(varLED)
	{
		case 1	:	port = GPIO_PORT_LED_12;	pin  = GPIO_PIN_LED_1;	break;
		case 2	:	port = GPIO_PORT_LED_12;	pin  = GPIO_PIN_LED_2;	break;
		case 3	:	port = GPIO_PORT_LED_34;	pin  = GPIO_PIN_LED_3;	break;
		case 4	:	port = GPIO_PORT_LED_34;	pin  = GPIO_PIN_LED_4;	break;
		default	: 														break;
	}
	
	/* Setup */
	gpioOutputSetup(port, pin);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioLEDState
 *	Purpose	:	Control LED's state
 *	Input	:	varLED: Number to indicate LED (1, 2, 3, 4)
 *				state: State of LED (0 for Low, 1 for High, 2 for Toggle)
 *	Output	:	None
 */
void	gpioLEDState(uint8_t varLED, uint8_t state)
{
	/* Declare */
	uint32_t port, pin;
	
	/* Assign port and pin */
	switch(varLED)
	{
		case 1	:	port = GPIO_PORT_LED_12;	pin  = GPIO_PIN_LED_1;	break;
		case 2	:	port = GPIO_PORT_LED_12;	pin  = GPIO_PIN_LED_2;	break;
		case 3	:	port = GPIO_PORT_LED_34;	pin  = GPIO_PIN_LED_3;	break;
		case 4	:	port = GPIO_PORT_LED_34;	pin  = GPIO_PIN_LED_4;	break;
		default	: 														break;
	}
	
	/* Control state */
	switch(state)
	{
		case 0	:	gpioLow		(port, pin);	break;	// Low
		case 1	:	gpioHigh	(port, pin);	break;	// High
		case 2	:	gpioToggle(port, pin);		break;	// Toggle
		default	:								break;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioBtnSetup
 *	Purpose	:	Setup Button
 *	Input	:	varBtn: Number indicates button (1, 2)
 *	Output	:	None
 */
void	gpioBtnSetup(uint8_t varBtn)
{
	/* Declare */
	uint32_t port = GPIO_PORT_BTN, pin;
	
	/* Assign port and pin */
	switch(varBtn)
	{
		case 1	:	pin  = GPIO_PIN_BTN_1;	break;
		case 2	:	pin  = GPIO_PIN_BTN_2;	break;
		default	: 							break;
	}
	
	/* Setup as input */
	gpioInputSetup(port, pin, GPIO_IN_PULL_UP);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioBtnSetup
 *	Purpose	:	Setup Button as interrupt
 *	Input	:	varBtn: Number indicates button (1, 2)
 *				GPIO_BTN_ISR: Handler
 *	Output	:	None
 */
void	gpioBtnIntSetup(uint8_t varBtn, void (*GPIO_BTN_ISR)(void))
{
	/* Declare */
	uint32_t port = GPIO_PORT_BTN, pin;
	
	/* Assign port and pin */
	switch(varBtn)
	{
		case 1	:	pin  = GPIO_PIN_BTN_1;	break;
		case 2	:	pin  = GPIO_PIN_BTN_2;	break;
		default	: 							break;
	}
	
	/* Setup as input */
	gpioInputSetup(port, pin, GPIO_IN_PULL_UP);
	
	/* Setup interrupt */
	gpioIntSetup(port, pin, GPIO_IN_DETECT_FALL, GPIO_BTN_ISR);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	gpioBtnRead
 *	Purpose	:	Read data from button
 *	Input		:	varBtn: Number indicates button (1, 2)
 *	Output	:	Data
 */
uint8_t	gpioBtnRead(uint8_t varBtn)
{
	/* Declare */
	uint32_t port = GPIO_PORT_BTN, pin;
	
	/* Assign pin */
	switch(varBtn)
	{
		case 1	:	pin = GPIO_PIN_BTN_1;	break;
		case 2	:	pin = GPIO_PIN_BTN_2;	break;
		default	:							break;
	}
	
	/* Read and return */
	return gpioRead(port, pin);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input		:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input		:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------



/**************************************************************************************************
 *	END OF GPIO.1.0.1.c
 *************************************************************************************************/

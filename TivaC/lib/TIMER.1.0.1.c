/*
 *	File			:	TIMER.1.0.1.c
 *	Date created	:	22/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	1.0.1
 *	Description		:	Library of TIMER
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
  /* Standard Library */
 
 /* Producing Library */
 
 /* My Library */
 #include "TIMER.1.0.1.h"

 /* This project */
 
 
/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Get Timer peripheral */
#define	GET_TIMER_PERIPH(TIMER)				SYSCTL_PERIPH_##TIMER

/*
 *	Purpose	:	Enable Timer
 *	Input	:	TIMER: Timer module (7:0)
 *	Output	:	None
 */
static	void	timerEnable(uint32_t TIMER)
{
	/* Enable */
	switch (TIMER)
	{
		case TIMER0:
			SysCtlPeripheralEnable(GET_TIMER_PERIPH(TIMER0));
			while(!SysCtlPeripheralReady(GET_TIMER_PERIPH(TIMER0)));
			break;
		case TIMER1:
			SysCtlPeripheralEnable(GET_TIMER_PERIPH(TIMER1));
			while(!SysCtlPeripheralReady(GET_TIMER_PERIPH(TIMER1)));
			break;
		case TIMER2:
			SysCtlPeripheralEnable(GET_TIMER_PERIPH(TIMER2));
			while(!SysCtlPeripheralReady(GET_TIMER_PERIPH(TIMER2)));
			break;
		case TIMER3:
			SysCtlPeripheralEnable(GET_TIMER_PERIPH(TIMER3));
			while(!SysCtlPeripheralReady(GET_TIMER_PERIPH(TIMER3)));
			break;
		case TIMER4:
			SysCtlPeripheralEnable(GET_TIMER_PERIPH(TIMER4));
			while(!SysCtlPeripheralReady(GET_TIMER_PERIPH(TIMER4)));
			break;
		case TIMER5:
			SysCtlPeripheralEnable(GET_TIMER_PERIPH(TIMER5));
			while(!SysCtlPeripheralReady(GET_TIMER_PERIPH(TIMER5)));
			break;
		case TIMER6:
			SysCtlPeripheralEnable(GET_TIMER_PERIPH(TIMER6));
			while(!SysCtlPeripheralReady(GET_TIMER_PERIPH(TIMER6)));
			break;
		case TIMER7:
			SysCtlPeripheralEnable(GET_TIMER_PERIPH(TIMER7));
			while(!SysCtlPeripheralReady(GET_TIMER_PERIPH(TIMER7)));
			break;
	}
}

//-------------------------------------------------------------------------------------------------
/* Get Timer interrupt */
#define	GET_TIMER_INT(x, y)				INT_##x##y		// x is TIMER, y is TIMER_

/*
 *	Purpose	:	Enable Timer interrupt
 *	Input	:	TIMER : Timer module (7:0)
 *				TIMER_: Timer sub (A or B)
 *	Output	:	None
 */
static	void	intEnableTimer(uint32_t TIMER, uint32_t TIMER_)
{
	switch(TIMER)
	{
	case TIMER0:
		if(TIMER_A)	IntEnable(GET_TIMER_INT(TIMER0, A));
		else		IntEnable(GET_TIMER_INT(TIMER0, B));
		break;
	case TIMER1:
		if(TIMER_A)	IntEnable(GET_TIMER_INT(TIMER1, A));
		else		IntEnable(GET_TIMER_INT(TIMER1, B));
		break;
	case TIMER2:
		if(TIMER_A)	IntEnable(GET_TIMER_INT(TIMER2, A));
		else		IntEnable(GET_TIMER_INT(TIMER2, B));
		break;
	case TIMER3:
		if(TIMER_A)	IntEnable(GET_TIMER_INT(TIMER3, A));
		else		IntEnable(GET_TIMER_INT(TIMER3, B));
		break;
	case TIMER4:
		if(TIMER_A)	IntEnable(GET_TIMER_INT(TIMER4, A));
		else		IntEnable(GET_TIMER_INT(TIMER4, B));
		break;
	case TIMER5:
		if(TIMER_A)	IntEnable(GET_TIMER_INT(TIMER5, A));
		else		IntEnable(GET_TIMER_INT(TIMER5, B));
		break;
	case TIMER6:
		if(TIMER_A)	IntEnable(GET_TIMER_INT(TIMER6, A));
		else		IntEnable(GET_TIMER_INT(TIMER6, B));
		break;
	case TIMER7:
		if(TIMER_A)	IntEnable(GET_TIMER_INT(TIMER7, A));
		else		IntEnable(GET_TIMER_INT(TIMER7, B));
		break;
	}
}

//-------------------------------------------------------------------------------------------------
/* Indicate whether Timer for delay is setupped */
static	bool	isTimerDelaySetup = false;

/* Indicate timer delay interrupt is reached */
static	bool	isReachDelayIntv = false;

/*
 *	Purpose	:	Handler for Timer7 - sub A interrupt
 *	Input	:	None
 *	Output	:	None
 */
void	TIMER7A_Handler(void)
{
	/* Exit timer interrupt */
	TimerIntClear(TIMER7, TIMER_TIMA_TIMEOUT);

	/* Set Delay flag */
	isReachDelayIntv = true;
}


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/*
 *	Purpose	:	Setup timer
 *	Input	:	TIMER 		:	Module (7 : 0)
 *				TIMER_ 		:	SubTimer (A or B)
 *				TIMER_CLK_ 	:	Clock source
 *				TIMER_CFG_ 	:	Config mode
 *				isInt 		:	Whether using interrupt handler
 *				varPreScl 	:	Prescale the input clock
 *				varTmo 		:	Timeout interval
 *	Output	:	None
 */
void	timerSetup(uint32_t TIMER, uint32_t TIMER_, uint32_t TIMER_CFG_, bool isInt,
																uint32_t varPreScl, uint32_t varTmo)
{
    /* Enable module */
	timerEnable(TIMER);									// Enable module Timer
	
	/* Enable Master interrupt */
	if(isInt)	IntMasterEnable();

    /* Configure 32-bit periodic timer */
    TimerConfigure(TIMER, TIMER_CFG_);					// Config mode
	TimerLoadSet(TIMER, TIMER_, varTmo);				// Set upper bound for timeout interval
	
    /* Setup the interrupts for the timer timeouts */
	if(isInt)
	{
		intEnableTimer(TIMER, TIMER_);					// Enable Interrupt module Timer
		TimerIntEnable(TIMER, TIMER_TIMA_TIMEOUT);		// Enable Timer interrupt
	}

    /* Enable the timers */
//    TimerEnable(TIMER, TIMER_);							// Enable Timer
}
//-------------------------------------------------------------------------------------------------
/*
 *  Purpose :
 *  Input   :
 *  Output  :
 */
void    timerStart(uint32_t TIMER, uint32_t TIMER_)
{
    TimerEnable(TIMER, TIMER_);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void	timerStop(uint32_t TIMER, uint32_t TIMER_)
{
	TimerDisable(TIMER, TIMER_);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void	timerIntExit(uint32_t TIMER, uint32_t TIMER_)
{
	if		(TIMER_ == TIMER_A)	TimerIntClear(TIMER, TIMER_TIMA_TIMEOUT);
	else if (TIMER_ == TIMER_A)	TimerIntClear(TIMER, TIMER_TIMB_TIMEOUT);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void	timerTimeoutSet(uint32_t TIMER, uint32_t TIMER_, uint32_t varLoad)
{
	TimerLoadSet(TIMER, TIMER_, varLoad);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
uint32_t	timerTimeoutGet(uint32_t TIMER, uint32_t TIMER_)
{
	return TimerValueGet(TIMER, TIMER_);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:	Delay using Timer (Each counting unit is a  clock cycle)
 *	Input	:	varTimerTmo : How many counting units to wait
 *	Output	:	None
 */
void	timerDelay(uint32_t varTimerTmo)
{
	/* If Timer for delay is setupped */
	if(isTimerDelaySetup)
	{
		/* Load Timeout interval */
		HWREG(TIMER7 + TIMER_O_TAILR) = varTimerTmo - 10;

		/* Enable timer7 - sub A */
		HWREG(TIMER7 + TIMER_O_CTL) |= TIMER_A & (TIMER_CTL_TAEN | TIMER_CTL_TBEN);

		/* Wait until the flag isReachDelayIntv is set */
		while(!isReachDelayIntv);

		/* Clear flag isReachDelayIntv */
		isReachDelayIntv = false;
	}

	/* If Timer for delay is not setupped, just for the first time call this function */
	else
	{
		/* Setup Timer7 - sub A */
		timerSetup(TIMER7, TIMER_A, TIMER_CFG_PERIODIC_UP, true, 1, varTimerTmo - 10);
		
		/* Wait until the flag isReachDelayIntv is set */
		while(!isReachDelayIntv);

		/* Clear flag isReachDelayIntv */
		isReachDelayIntv = false;

		/* Set flag isTimerDelaySetup */
		isTimerDelaySetup = true;
	}
	
	/* Disable timer */
	HWREG(TIMER7 + TIMER_O_CTL) &= ~(TIMER_A & (TIMER_CTL_TAEN | TIMER_CTL_TBEN));
}
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------
/*
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF TIMER.1.0.1.c
 *************************************************************************************************/

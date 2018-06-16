/*
 *  Author      : Thuy Nguyen-Chinh.
 *  Date        : 23/09/2017.
 *  Description : Driver LCD 16x2 for TivaC-1294 NCPDT.
 *  Version     : 1.0.1.
 */
/******************************************************************************
 *  Include
 *****************************************************************************/
#include "LCD162.1.0.1.h"


/******************************************************************************
 *  Public
 *****************************************************************************/


/******************************************************************************
 *  Private
 *****************************************************************************/
/* Control signals */
static  uint32_t    lcdPortCtrl;        // Control port
static  uint8_t     lcdPinRS;           // Register select pin
static  uint8_t     lcdPinEN;           // Enable pin

/* Data signals */
static  uint32_t    lcdPortData;        // Data port
static  uint8_t     lcdDataOffset;      // Data-pin offset from the MSB bit


/******************************************************************************
 *  Function
 *****************************************************************************/
/*
 *  Function: Initialize the LCD.
 *
 *  Input   : LCD_PORT_CTRL_    : xxxxxxxxxx
 *            LCD_PIN_RS_       : xxxxxxxxxx
 *            LCD_PIN_EN_       : xxxxxxxxxx
 *            LCD_PORT_DATA_    : xxxxxxxxxx
 *            LCD_DATA_OFFSET   : xxxxxxxxxx
 *
 *  Output  : (void)
 */
void LCD_Setup(uint32_t LCD_PORT_CTRL_, uint8_t LCD_PIN_RS_, uint8_t LCD_PIN_EN_,
               uint32_t LCD_PORT_DATA_, uint8_t LCD_DATA_OFFSET_)
{
    /* Assign variable */
    lcdPortCtrl     = LCD_PORT_CTRL_;
    lcdPinRS        = LCD_PIN_RS_;
    lcdPinEN        = LCD_PIN_EN_;
    lcdPortData     = LCD_PORT_DATA_;
    lcdDataOffset   = LCD_DATA_OFFSET_;

    /* Setup GPIO */
    gpioOutputSetup(lcdPortData, 0xF0>>lcdDataOffset);
    gpioOutputSetup(lcdPortCtrl, lcdPinRS | lcdPinEN);

    /* Initialize LCD */
    clkDelayMs(2);                          // Delay 1.64mS
    LCD_Init_write(0x20);                   // 4 bit mode, delay 40uS
    LCD_Command(0x28);
    clkDelayMs(2);
    LCD_Command(0x0C);                      // Bat hien thi,tat con tro, delay 40uS
    clkDelayMs(2);
    ///////////////////////////////////////////
    LCD_Command(6);                         // Hien thi tang va khong shift, delay 40uS
    clkDelayMs(2);
    ///////////////////////////////////////////
    LCD_Command(0x01);                      //Xoa man hinh hien thi
    clkDelayMs(2);
    ///////////////////////////////////////////
    clkDelayMs(2);                          // Delay 1.64mS
    LCD_Command(0x02);                      //Tro ve dau dong
    clkDelayMs(2);                          // Delay 1.64mS
}
//-----------------------------------------------------------------------------
/*
 *  Function: Write 8-bit data into LCD in the initialization.
 *
 *  Input   : b : 8-bit data.
 *
 *  Output  : (void)
 */
void LCD_Init_write(uint8_t data)
{
	gpioLow(lcdPortData, 0xF0>>lcdDataOffset);
	gpioLow(lcdPortCtrl, lcdPinRS);
	clkDelayMs(2);

	data &= 0xF0;

    gpioHigh(lcdPortData, data>>lcdDataOffset);

	gpioHigh(lcdPortCtrl, lcdPinEN);
    clkDelayMs(2);
    gpioLow(lcdPortCtrl, lcdPinEN);

    clkDelayMs(2);
}
//-----------------------------------------------------------------------------
/*
 *  Function: Write command into LCD.
 *
 *  Input   : cmd : Command of LCD.
 *
 *  Output  : (void)
 */
void LCD_Command(uint8_t cmd)
{
	uint8_t HNib, LNib;
    HNib = (cmd & 0xF0);
    LNib = ((cmd<<4) & 0xF0);

    gpioLow(lcdPortData, 0xF0>>lcdDataOffset);
	gpioHigh(lcdPortData, HNib>>lcdDataOffset);
	gpioHigh(lcdPortCtrl, lcdPinEN);
    clkDelayMs(2);
	gpioLow(lcdPortCtrl, lcdPinEN);
	clkDelayMs(2);

    gpioLow(lcdPortData, 0xF0>>lcdDataOffset);
    gpioHigh(lcdPortData, LNib>>lcdDataOffset);
    gpioHigh(lcdPortCtrl, lcdPinEN);
    clkDelayMs(2);
    gpioLow(lcdPortCtrl, lcdPinEN);
	clkDelayMs(2);
}
//-----------------------------------------------------------------------------
/*
 *  Function: Clear LCD screen.
 *
 *  Input   : (void)
 *
 *  Output  : (void)
 */
void LCD_Clear()
{
	gpioLow(lcdPortCtrl, lcdPinRS);
	LCD_Command(0x01);
	clkDelayMs(2);
}
//-----------------------------------------------------------------------------
/*
 *  Function: Move the cursor back to the original position.
 *
 *  Input   : (void)
 *
 *  Output  : (void)
 */
void LCD_Home()
{
    gpioLow(lcdPortCtrl, lcdPinRS);
	LCD_Command(0x02);
	clkDelayMs(2);
}
//-----------------------------------------------------------------------------
/*
 *  Function: Display character into the LCD screen.
 *
 *  Input   : chr : Character.
 *
 *  Output  : (void)
 */
void LCD_Display(uint8_t chr)
{
	gpioHigh(lcdPortCtrl, lcdPinRS);
	LCD_Command(chr);
}
//-----------------------------------------------------------------------------
/*
 *  Function: Move cursor to a position indexed by [row] and [column].
 *
 *  Input   : row   : Row index (1 or 2).
 *            column: Column index (1-16).
 *
 *  Output  : (void)
 */
void LCD_Goto(uint8_t row, uint8_t column)
{
	gpioLow(lcdPortCtrl, lcdPinRS);
	if(row == 2)
		LCD_Command(0xC0 + column - 1);
	else
		LCD_Command(0x80 + column - 1);
}
//-----------------------------------------------------------------------------
/*
 *  Function: Move cursor to the right or the left by number of [step] position.
 *
 *  Input   : direct: Right(0) or Left(1).
 *            step  : How many step distance?
 *
 *  Output  : (void).
 */
void LCD_CursorShift(uint8_t direct, uint8_t step)
{
	uint8_t i;
	gpioLow(lcdPortCtrl, lcdPinRS);
	if (direct == 0)
		for(i=0; i<step; i++)
			LCD_Command(0x10);
	else
		for(i=0; i<step; i++)
			LCD_Command(0x14);
}
//-----------------------------------------------------------------------------
/*
 *  Function: Display a string into the LCD screen.
 *
 *  Input   : str : String of character.
 *
 *  Output  : (void)
 */
void LCD_PrintString(char *str)
{
	while(*str)
	{
		LCD_Display(*str);
		str++;
	}
}
//-----------------------------------------------------------------------------
/*
 *  Function: xxxxxxxxxx
 *
 *  Input   : xxxxx : xxxxxxxxxx
 *            xxxxx : xxxxxxxxxx
 *
 *  Output  : xxxxx : xxxxxxxxxx
 *            xxxxx : xxxxxxxxxx
 */
/* In ra man hinh so nguyen n voi so cho hien thi bang length(chua ke vi tri cua dau) */
void LCD_PrintDecimal(long n, uint8_t length)
{
	uint8_t du,luu=length;
	// de trong 1 ki tu o dau cho hien thi dau
	if(n>=0)LCD_Display(' ');		//In so duong	
	else 
	{
		LCD_Display('-');			//In so am
		n*=-1;
	}	
	
	length--;
	LCD_CursorShift(1,length-1);	// dich con tro sang phai length-1 vi tri
	lcdPortCtrl &= ~lcdPinRS;
	clkDelayMs(2);
	LCD_DEC_CUR_SHIFT_OFF();		// chuyen sang che do in lui
	// Bat dau in lan luot cac chu so tu hang don vi
	while(length)
	{
		du = n % 10;
		n = n / 10;
		LCD_Display(0x30 + du);
		length--;
	}
	LCD_CursorShift(1,luu);		// dua con tro sang phai length+1 vi tri de in tiep
	lcdPortCtrl &= ~lcdPinRS;
	clkDelayMs(2);
	LCD_INC_CUR_SHIFT_OFF();		// chuyen lai ve che do in xuoi
}
//-----------------------------------------------------------------------------
/*
 *  Function: xxxxxxxxxx
 *
 *  Input   : xxxxx : xxxxxxxxxx
 *            xxxxx : xxxxxxxxxx
 *
 *  Output  : xxxxx : xxxxxxxxxx
 *            xxxxx : xxxxxxxxxx
 */
void LCD_PrintUnDecimal(long n, uint8_t length)
{
	uint8_t du,luu=length;
	LCD_CursorShift(1,length-1);	// dich con tro sang phai length-1 vi tri
	lcdPortCtrl &=~ lcdPinRS;
	clkDelayMs(2);
	LCD_DEC_CUR_SHIFT_OFF();		// chuyen sang che do in lui
	// Bat dau in lan luot cac chu so tu hang don vi
	while(length)
	{
		du = n % 10;
		n = n / 10;
		LCD_Display(0x30 + du);
		length--;
	}
	LCD_CursorShift(1,luu+1);		// dua con tro sang phai length+1 vi tri de in tiep
	lcdPortCtrl &= ~lcdPinRS;
	clkDelayMs(2);
	LCD_INC_CUR_SHIFT_OFF();		// chuyen lai ve che do in xuoi
	
	
}
//-----------------------------------------------------------------------------
/*
 *  Function: xxxxxxxxxx
 *
 *  Input   : xxxxx : xxxxxxxxxx
 *            xxxxx : xxxxxxxxxx
 *
 *  Output  : xxxxx : xxxxxxxxxx
 *            xxxxx : xxxxxxxxxx
 */
/* In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma */
void LCD_PrintFloat(float x, uint8_t length, uint8_t coma)
{
	// de trong 1 ki tu o dau cho hien thi dau
	if(x>=0)LCD_Display(' ');
	else 
	{
		LCD_Display('-');			//In so am
		x*=-1;
	}
	unsigned long n;
	uint8_t store,temp;
	store = length;						// Luu lai do dai so thuc.
	length--;								// Giam di 1 cho dau "."						
	for(temp=0;temp<coma;temp++)
		x = x*10;
	
	n = x;									// Chuyan thanh so nguyen.
	if((x-n)>=0.5)n++;

	LCD_CursorShift(1,length);				// Dich chuyen con tro sang phai
	lcdPortCtrl &= ~lcdPinRS;
	clkDelayMs(2);
	LCD_DEC_CUR_SHIFT_OFF();				// Chuyen sang che do in nguoc.

	while(coma)								// In ra phan truoc dau phay
	{
		temp = n % 10;
		n = n / 10;
		LCD_Display(0x30 + temp);
		coma--;
		length--;
	}

	LCD_Display('.');							// In ra dau "."
	
		while(length)							// In ra phan thap phan
		{
			temp = n % 10;
			n = n / 10;
			//if(temp!=n)
			LCD_Display(0x30 + temp);			
			length--;
		}
		lcdPortCtrl &= ~lcdPinRS;
	clkDelayMs(2);
	LCD_INC_CUR_SHIFT_OFF();				// Chuyen lai che do in thuan.
	LCD_CursorShift(1,store+1);					// Nhay den vi tri tiep theo.
}


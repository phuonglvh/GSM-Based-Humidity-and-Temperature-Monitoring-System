/*
 *	Author	    : Thuy Nguyen-Chinh.
 *	Date	    : 23/09/2017.
 *	Description : Driver LCD 16x2 for TivaC-1294 NCPDT.
 *	Version	    : 1.0.1.
 */
#ifndef LCD162_1_0_1_H_
#define LCD162_1_0_1_H_
/******************************************************************************
 *	INCLUDEs
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include "CLK.1.0.1.h"
#include "GPIO.1.0.1.h"


/******************************************************************************
 *	DEFINITIONs
 *****************************************************************************/
/* Chon kieu hien thi tang/giam, shift hoac khong shift */
#define LCD_DEC_CUR_SHIFT_ON()	LCD_Command(0x05);
#define LCD_DEC_CUR_SHIFT_OFF()	LCD_Command(0x04);
#define LCD_INC_CUR_SHIFT_ON()	LCD_Command(0x07);
#define LCD_INC_CUR_SHIFT_OFF()	LCD_Command(0x06);	// khuyen khich su dung cach nay


/******************************************************************************
 *	PUBLICs
 *****************************************************************************/


/******************************************************************************
 *	FUNCTIONs
 *****************************************************************************/
/* Setup */
void
LCD_Setup
(uint32_t LCD_PORT_CTRL_, uint8_t LCD_PIN_RS_, uint8_t LCD_PIN_EN_,
 uint32_t LCD_PORT_DATA_, uint8_t LCD_DATA_OFFSET_);

/* Write 8-bit data into LCD */
void LCD_Init_write(uint8_t b);

/* Write 2 nibbles into LCD */
void LCD_Command(uint8_t chr);

/* Read data from LCD */
uint8_t LCD_Read2Nib();

/* Intialize LCD */
void LCD_Init();

/* Clear LCD screen */
void LCD_Clear();

/*  */
void LCD_Home();

/* Display character on the LCD screen */
void LCD_Display(uint8_t chr);

/* Move cursor to a position indexed by [row] and [column] */
void LCD_Goto(uint8_t row, uint8_t column);

/* Move cursor to the right ([direct]=0) or the left ([direct]=1) by number of [step] position */
void LCD_CursorShift(uint8_t direct, uint8_t step);

/* Display a string into LCD screen */
void LCD_PrintString(char *str);

/* In ra man hinh so nguyen n voi so cho hien thi bang length(chua ke vi tri cua dau) */
void LCD_PrintDecimal(long n, uint8_t length);

/*  */
void LCD_PrintUnDecimal(long n, uint8_t length);

/* In ra man hinh so thuc x voi so cho hien thi = length, so chu so sau dau phay la coma */
void LCD_PrintFloat(float x, uint8_t length, uint8_t coma);



#endif /* LCD162_1_0_1_H_ */


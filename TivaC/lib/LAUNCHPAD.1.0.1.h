/*
 *	File			:	LAUNCHPAD.1.0.1.h
 *	Date created	:	08/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	1.0.1
 *	Description		:	Hardware of The Connected LaunchPad EK-TM4C1294XL
 */
#ifndef LAUNCHPAD_1_0_1_H_
#define LAUNCHPAD_1_0_1_H_
/**************************************************************************************************
 *	INCLUDE
 *************************************************************************************************/
 /* Standard Library */
#include <stdint.h>
#include <stdbool.h>

 /* Producing Library */
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"

 /* My Library */

 /* This project */


/**************************************************************************************************
 *	HARDWARE MAP
 *************************************************************************************************/
/* Booster Pack 1 */
//	Header A1		Header B1							Header C1		Header D1
//	PIN_BP1L_0		PIN_BP1L_10							PIN_BP1R_0		PIN_BP1R_10
//	PIN_BP1L_1		PIN_BP1L_11							PIN_BP1R_1		PIN_BP1R_11
//	PIN_BP1L_2		PIN_BP1L_12							PIN_BP1R_2		PIN_BP1R_12
//	PIN_BP1L_3		PIN_BP1L_13							PIN_BP1R_3		PIN_BP1R_13
//	PIN_BP1L_4		PIN_BP1L_14							PIN_BP1R_4		PIN_BP1R_14
//	PIN_BP1L_5		PIN_BP1L_15							PIN_BP1R_5		PIN_BP1R_15
//	PIN_BP1L_6		PIN_BP1L_16							PIN_BP1R_6		PIN_BP1R_16
//	PIN_BP1L_7		PIN_BP1L_17							PIN_BP1R_7		PIN_BP1R_17
//	PIN_BP1L_8		PIN_BP1L_18							PIN_BP1R_8		PIN_BP1R_18
//	PIN_BP1L_9		PIN_BP1L_19							PIN_BP1R_9		PIN_BP1R_19
//
//-------------------------------------------------------------------------------------------------
/* Booster Pack 2 */
//	Header A2		Header B2							Header C2		Header D2
//	PIN_BP2L_0		PIN_BP2L_10							PIN_BP2R_0		PIN_BP2R_10
//	PIN_BP2L_1		PIN_BP2L_11							PIN_BP2R_1		PIN_BP2R_11
//	PIN_BP2L_2		PIN_BP2L_12							PIN_BP2R_2		PIN_BP2R_12
//	PIN_BP2L_3		PIN_BP2L_13							PIN_BP2R_3		PIN_BP2R_13
//	PIN_BP2L_4		PIN_BP2L_14							PIN_BP2R_4		PIN_BP2R_14
//	PIN_BP2L_5		PIN_BP2L_15							PIN_BP2R_5		PIN_BP2R_15
//	PIN_BP2L_6		PIN_BP2L_16							PIN_BP2R_6		PIN_BP2R_16
//	PIN_BP2L_7		PIN_BP2L_17							PIN_BP2R_7		PIN_BP2R_17
//	PIN_BP2L_8		PIN_BP2L_18							PIN_BP2R_8		PIN_BP2R_18
//	PIN_BP2L_9		PIN_BP2L_19							PIN_BP2R_9		PIN_BP2R_19


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Booster Pack 1 */
//-Left-//
	//-Header A1-//
#define	PIN_BP1L_0				// +3V3			// +3V3
#define	PIN_BP1L_1				// Analog		// PE4
#define	PIN_BP1L_2				// UART7 RX		// PC4
#define	PIN_BP1L_3				// UART7 TX		// PC5
#define	PIN_BP1L_4				// GPIO			// PC6
#define	PIN_BP1L_5				// Analog		// PE5
#define	PIN_BP1L_6				// SPI CLK		// PD3
#define	PIN_BP1L_7				// GPIO			// PC7
#define	PIN_BP1L_8				// I2C0 SCL		// PB2
#define	PIN_BP1L_9				// I2C0 SDA		// PB3_SDA

	//-Header B1-//
#define	PIN_BP1L_10				// +5V			// +5V
#define	PIN_BP1L_11				// Analog		// GND
#define	PIN_BP1L_12				// Analog		// PE0
#define	PIN_BP1L_13				// Analog		// PE1
#define	PIN_BP1L_14				// Analog		// PC2
#define	PIN_BP1L_15				// Analog		// PE3
#define	PIN_BP1L_16				// Analog		// PD7
#define	PIN_BP1L_17				// Analog		// PA6
#define	PIN_BP1L_18				// A Out		// PM4
#define	PIN_BP1L_19				// A Out		// PM5

//-	Right -//
		//-Header C1-//
#define	PIN_BP1R_0				// PWM			// PF1
#define	PIN_BP1R_1				// PWM			// PF2
#define	PIN_BP1R_2				// PWM			// PF3
#define	PIN_BP1R_3				// PWM			// PG0
#define	PIN_BP1R_4				// Capture		// PL4
#define	PIN_BP1R_5				// Capture		// PL5
#define	PIN_BP1R_6				// GPIO			// PL0
#define	PIN_BP1R_7				// GPIO			// PL1
#define	PIN_BP1R_8				// GPIO			// PL2
#define	PIN_BP1R_9				// GPIO			// PL3

	//-Header D1-//
#define	PIN_BP1R_10				// GND			// GND
#define	PIN_BP1R_11				// PWM			// PM3
#define	PIN_BP1R_12				// GPIO			// PH2
#define	PIN_BP1R_13				// GPIO			// PH3
#define	PIN_BP1R_14				// RESET		// RESET
#define	PIN_BP1R_15				// SPI MOSI		// PD1
#define	PIN_BP1R_16				// SPI MISO		// PD0
#define	PIN_BP1R_17				// GPIO			// PN2
#define	PIN_BP1R_18				// GPIO			// PN3
#define	PIN_BP1R_19				// GPIO			// PP2

//-------------------------------------------------------------------------------------------------
/* Booster Pack 2 */
//-Left-//
	//-Header A2-//
#define	PIN_BP2L_0				// +3V3			// +3V3
#define	PIN_BP2L_1				// Analog		// PD2
#define	PIN_BP2L_2				// UART6 RX		// PP0
#define	PIN_BP2L_3				// UART6 TX		// PP1
#define	PIN_BP2L_4				// GPIO(JP4)	// PD4
												// PA0
#define	PIN_BP2L_5				// Analog(JP5)	// PD5
												// PA1
#define	PIN_BP2L_6				// SPI CLK		// PQ0
#define	PIN_BP2L_7				// GPIO			// PP4
#define	PIN_BP2L_8				// I2C2 SCL		// PN5
#define	PIN_BP2L_9				// I2C2 SDA		// PN4
	//-Header B2-//
#define	PIN_BP2L_10				// +5V			// +5V
#define	PIN_BP2L_11				// GND			// GND
#define	PIN_BP2L_12				// Analog		// PB4
#define	PIN_BP2L_13				// Analog		// PB5
#define	PIN_BP2L_14				// Analog		// PK0
#define	PIN_BP2L_15				// Analog		// PK1
#define	PIN_BP2L_16				// Analog		// PK2
#define	PIN_BP2L_17				// Analog		// PK3
#define	PIN_BP2L_18				// A out		// PA4
#define	PIN_BP2L_19				// A out		// PA5

//-	Right -//
	//-Header C2-//
#define	PIN_BP2R_0				// PWM			// PG1
#define	PIN_BP2R_1				// PWM			// PK4
#define	PIN_BP2R_2				// PWM			// PK5
#define	PIN_BP2R_3				// PWM			// PM0
#define	PIN_BP2R_4				// Capture		// PM1
#define	PIN_BP2R_5				// Capture		// PM2
#define	PIN_BP2R_6				// GPIO			// PH0
#define	PIN_BP2R_7				// GPIO			// PH1
#define	PIN_BP2R_8				// GPIO			// PK6
#define	PIN_BP2R_9				// GPIO			// PK7

	//-Header D2-//
#define	PIN_BP2R_10				// GND			// GND
#define	PIN_BP2R_11				// PWM			// PM7
#define	PIN_BP2R_12				// GPIO			// PP5
#define	PIN_BP2R_13				// GPIO			// PA7
#define	PIN_BP2R_14				// RESET		// RESET
#define	PIN_BP2R_15				// SPI MOSI		// PQ2
								// I2C8	SDA		// PA3
#define	PIN_BP2R_16				// SPI MISO		// PQ3
								// I2C8	SCL		// PA2
#define	PIN_BP2R_17				// GPIO			// PP3
#define	PIN_BP2R_18				// GPIO			// PQ1
#define	PIN_BP2R_19				// GPIO			// PM6

//-------------------------------------------------------------------------------------------------
/* Breadboard connection */
	//-Odd-//
#define	PIN_BREAD_1				// 3V3
#define	PIN_BREAD_3				// GND
#define	PIN_BREAD_5				// PB4
#define	PIN_BREAD_7				// PB5
#define	PIN_BREAD_9				// PH0
#define	PIN_BREAD_11			// PH1
#define	PIN_BREAD_13			// PH2
#define	PIN_BREAD_15			// PH3
#define	PIN_BREAD_17			// PC7
#define	PIN_BREAD_19			// PC6
#define	PIN_BREAD_21			// PC5
#define	PIN_BREAD_23			// PC4
#define	PIN_BREAD_25			// PA6
#define	PIN_BREAD_27			// PA7
#define	PIN_BREAD_29			// PG1
#define	PIN_BREAD_31			// PG0
#define	PIN_BREAD_33			// PM3
#define	PIN_BREAD_35			// GND
#define	PIN_BREAD_37			// PM2
#define	PIN_BREAD_39			// PM1
#define	PIN_BREAD_41			// PM0
#define	PIN_BREAD_43			// PL0
#define	PIN_BREAD_45			// PL1
#define	PIN_BREAD_47			// PL2
#define	PIN_BREAD_49			// PL3
#define	PIN_BREAD_51			// PQ0
#define	PIN_BREAD_53			// PQ1
#define	PIN_BREAD_55			// PQ2
#define	PIN_BREAD_57			// PQ3
#define	PIN_BREAD_59			// PK7
#define	PIN_BREAD_61			// GND
#define	PIN_BREAD_63			// PK6
#define	PIN_BREAD_65			// PL4
#define	PIN_BREAD_67			// PB2
#define	PIN_BREAD_69			// PB3
#define	PIN_BREAD_71			// PP2
#define	PIN_BREAD_73			// PP3
#define	PIN_BREAD_75			// PK5
#define	PIN_BREAD_77			// PK4
#define	PIN_BREAD_79			// PL5
#define	PIN_BREAD_81			// PN4
#define	PIN_BREAD_83			// PN5
#define	PIN_BREAD_85			// PN0
#define	PIN_BREAD_87			// PN1
#define	PIN_BREAD_89			// PN2
#define	PIN_BREAD_91			// PN3
#define	PIN_BREAD_93			// PQ4
#define	PIN_BREAD_95			// WAKE
#define	PIN_BREAD_97			// 5V

	//-Even-//
#define	PIN_BREAD_2				// 5V
#define	PIN_BREAD_4				// GND
#define	PIN_BREAD_6				// PA2
#define	PIN_BREAD_8				// PA3
#define	PIN_BREAD_10			// PA4
#define	PIN_BREAD_12			// PA5
#define	PIN_BREAD_14			// PE0
#define	PIN_BREAD_16			// PE1
#define	PIN_BREAD_18			// PE2
#define	PIN_BREAD_20			// PE3
#define	PIN_BREAD_22			// PE4
#define	PIN_BREAD_24			// PE5
#define	PIN_BREAD_26			// PK0
#define	PIN_BREAD_28			// PK1
#define	PIN_BREAD_30			// PK2
#define	PIN_BREAD_32			// PK3
#define	PIN_BREAD_34			// VREF
#define	PIN_BREAD_36			// GND
#define	PIN_BREAD_38			// PD5
#define	PIN_BREAD_40			// PD4
#define	PIN_BREAD_42			// PD7
#define	PIN_BREAD_44			// PD6
#define	PIN_BREAD_46			// PD3
#define	PIN_BREAD_48			// PD1
#define	PIN_BREAD_50			// PD0
#define	PIN_BREAD_52			// PD2
#define	PIN_BREAD_54			// PP0
#define	PIN_BREAD_56			// PP1
#define	PIN_BREAD_58			// PB0
#define	PIN_BREAD_60			// PB1
#define	PIN_BREAD_62			// GND
#define	PIN_BREAD_64			// PF4
#define	PIN_BREAD_66			// PF0
#define	PIN_BREAD_68			// PF1
#define	PIN_BREAD_70			// PF2
#define	PIN_BREAD_72			// PF3
#define	PIN_BREAD_74			// PA0
#define	PIN_BREAD_76			// PA1
#define	PIN_BREAD_78			// PP4
#define	PIN_BREAD_80			// PP5
#define	PIN_BREAD_82			// PJ0
#define	PIN_BREAD_84			// PJ1
#define	PIN_BREAD_86			// PM7
#define	PIN_BREAD_88			// PM6
#define	PIN_BREAD_90			// PM5
#define	PIN_BREAD_92			// PM4
#define	PIN_BREAD_94			// RESET
#define	PIN_BREAD_96			// GND
#define	PIN_BREAD_98			// 3V3

//-------------------------------------------------------------------------------------------------
/* Special modules */
//-LED-//
#define		GPIO_PORT_LED_12		GPIO_PORTN_BASE
#define		GPIO_PIN_LED_1			GPIO_PIN_1			// PN1
#define		GPIO_PIN_LED_2			GPIO_PIN_0			// PN0
#define		GPIO_PIN_LED_12			(GPIO_PIN_LED_1 + GPIO_PIN_LED_2)
#define		GPIO_PORT_LED_34		GPIO_PORTF_BASE
#define		GPIO_PIN_LED_3			GPIO_PIN_4			// PF4
#define		GPIO_PIN_LED_4			GPIO_PIN_0			// PF0
#define		GPIO_PIN_LED_34			(GPIO_PIN_LED_3 + GPIO_PIN_LED_4)

//-Button-//
#define		GPIO_PORT_BTN			GPIO_PORTJ_BASE
#define		GPIO_PIN_BTN_1			GPIO_PIN_1			// PJ1
#define		GPIO_PIN_BTN_2			GPIO_PIN_0			// PJ0
#define		GPIO_PIN_BTN_12			(GPIO_PIN_BTN_1 + GPIO_PIN_BTN_2)

//-UART-//
#define		UART_ICDI				UART0_BASE			// PA0_RX, PA1_TX
#define		UART_BP1L				UART7_BASE			// PC4_RX, PC5_TX
#define		UART_BP2L				UART6_BASE			// PP0_RX, PP1_TX

//-SSI-//

//-I2C-//
#define		I2C_MODULE_BP1L			I2C0_BASE			// PB2_SCL, PB3_SDA
#define		I2C_MODULE_BP2L			I2C2_BASE			// PN5_SCL, PN4_SDA
#define		I2C_MODULE_BP2R			I2C8_BASE			// PA2_SCL, PA3_SDA


/**************************************************************************************************
 *	FUNCTION
 *************************************************************************************************/
/* Bit access */
void
cbi		(uint32_t reg, uint8_t bit);
void
sbi		(uint32_t reg, uint8_t bit);

//-------------------------------------------------------------------------------------------------
/* Fast setup */
void
fastSetup(bool isUseLED, bool isUsedUART);

//-------------------------------------------------------------------------------------------------



/**************************************************************************************************
 *	END OF LAUNCHPAD.1.0.1.h
 *************************************************************************************************/
#endif /* LAUNCHPAD_1_0_1_H_ */

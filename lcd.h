/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.h
*
* PROJECT....: lcd_test
*
* DESCRIPTION: 
*
* Change Log:
* Mar 13, 2018 CREATED
*****************************************************************************/

#ifndef LCD_H_
#define LCD_H_	

/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/

#define CLEAR               0x01
#define HOME                0x02
#define NEWLINE             0xC0

#define CURSOR_SHIFT_LEFT   0b10000
#define CURSOR_SHIFT_RIGHT  0b10100
#define DISPLAY_SHIFT_LEFT  0b11000
#define DISPLAY_SHIFT_RIGHT 0b11100

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

void delay(INT32U);

void lcd_init(void);

void lcd_cmd(INT8U);

void lcd_display(INT8U);

void lcd_string(INT8U *);


/****************************** End Of Module *******************************/
#endif /* LCD_H_ */

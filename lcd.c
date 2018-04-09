/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.c
*
* PROJECT....: lcd_test
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
* Mar 13, 2018 CREATED 
*****************************************************************************/

/***************************** Include files *******************************/
#include "lcd.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>

/*****************************    Defines    *******************************/

#define D4  4
#define RS  2
#define E   3

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void delay(INT32U d)
{
    INT32U i = 0;

//    for (; d > 0 ; d--) {
//        for (i = 11998; i > 0; i--) {
//        }
//    }
    for (; d > 0 ; d--) {
        for (i = 1000; i > 0; i--) {
        }
    }
}

void lcd_cmd(INT8U c)
{
    /* for D7, D6, D5, D4 use
     *  PC7, PC6, PC5, PC4
     *      GPIO_PORTC_DATA_R
     *
     * for RS use PD2
     * for E use PD3 in
     *      GPIO_PORTD_DATA_R
     *
     * */

    /*
     * Sends commands to the LCD module
     * Therefore the RS pin is set to LOW
     * The code is written two time, because we are in 4 bit mode
     */

    // These two lines put most significant nibble into
    // the register on the LCD
    GPIO_PORTC_DATA_R &= ~(0xFF);
    GPIO_PORTC_DATA_R |= (c & 0xF0);

    // Clear RS and set E
    GPIO_PORTD_DATA_R |= 1 << E;        // E  = 1
    GPIO_PORTD_DATA_R &= ~(1 << RS);    // RS = 0

    delay(2);

    GPIO_PORTD_DATA_R &= ~(1 << E);     // E  = 0

    // Next nibble
    delay(2);

    GPIO_PORTC_DATA_R &= ~(0xFF);
    GPIO_PORTC_DATA_R |= (c & 0x0F) << D4;

    // Clear RS and set E
    GPIO_PORTD_DATA_R |= 1 << E;        // E  = 1
    GPIO_PORTD_DATA_R &= ~(1 << RS);    // RS = 0

    delay(2);

    GPIO_PORTD_DATA_R &= ~(1 << E);     // E = 0

    delay(2);
}

void lcd_display(INT8U c)
{
    GPIO_PORTC_DATA_R &= ~(0xFF);
    GPIO_PORTC_DATA_R |= (c & 0xF0);

    // Set RS and set E
    GPIO_PORTD_DATA_R |= 1 << E | 1 << RS;        // E  = 1, RS = 1

    delay(1);

    GPIO_PORTD_DATA_R &= ~(1 << E);     // E  = 0

    // Next nibble
    delay(1);

    GPIO_PORTC_DATA_R &= ~(0xFF);
    GPIO_PORTC_DATA_R |= (c & 0x0F) << D4;

    // Set RS and set E
    GPIO_PORTD_DATA_R |= 1 << E | 1 << RS;        // E  = 1, RS = 1

    delay(1);

    GPIO_PORTD_DATA_R &= ~(1 << E);     // E = 0

    delay(1);
}

void lcd_string (INT8U * msg)
{
    INT8U i = 0;

    while (msg[i] != 0)
    {
        lcd_display(msg[i]);
        i++;
    }
}

void lcd_init(void)
{
    INT8U dummy;

    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC | SYSCTL_RCGC2_GPIOD;

    dummy = SYSCTL_RCGC2_R;

    // Set direction as output (PD3, PD2)
    GPIO_PORTD_DIR_R |= 0b1100;

    // Set direction as output (PC7, PC6, PC5, PC4)
    GPIO_PORTC_DIR_R = 0b11110000;

    // Enable the GPIO pins for digital function (PD3, PD2)
    GPIO_PORTD_DEN_R |= 0b1100;

    // Enable the GPIO pins for digital function (PC7, PC6, PC5, PC4)
    GPIO_PORTC_DEN_R = 0b11110000;

//    lcd_cmd(0x02);  /* Initialize lcd in 4-bit mode */
//    lcd_cmd(0x28);  /* 2 lines */
//    lcd_cmd(0x0C);   /* Display on cursor off */
//    lcd_cmd(0x06);  /* Auto increment cursor */
//    lcd_cmd(0x01);   /* Display clear */
//    lcd_cmd(0x80);  /* First line first position */

    delay(100);

    lcd_cmd(0x03);

    delay(50);

    lcd_cmd(0x03);

    delay(10);

    lcd_cmd(0x03);
    lcd_cmd(0x02);  // Set 4 bit mode
    lcd_cmd(0x28);  // 4 bit mode, 1/16 duty, 5x8 font
    lcd_cmd(0x08);  // Display off
    lcd_cmd(0x0C);  // Display on, blink cursor on
    lcd_cmd(0x06);  // Entry mode
    lcd_cmd(0x01);  // Home
}

/****************************** End Of Module *******************************/

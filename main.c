
#include "messages.h"
#include "emp_type.h"
#include "queue.h"
#include "SPI.h"
#include "t_model.h"
#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "uart0.h"
#include <stdint.h>




/**
 * main.c
 */
int main(void)
{

    uart0_init(19200, 8, 1, 'n');
    INT16U dummy = 0;
    spi_init();
    lcd_init();
    lcd_cmd(CLEAR);
    lcd_display(51);
    INT16U LCD = 0;

    spi_write(set_pwm_1, 2+'0');
    while(spi_is_busy()){}
    spi_write(set_pwm_1, 7+'0');

while(1)
{
//    INT8U i;
//
//    for (i = 0; i < 255; ++i) {
//
//        for (LCD = 0; LCD < 10000; ++LCD) {
//
//        }
//        while(!(spi_write(set_pwm_1, i)))
//              {
//              }
//    }
    INT8U i;
    while(1)
    {
        while(spi_is_busy()){}
        while(!spi_data_rdy()){}
        dummy = 0;
        dummy = spi_read();

        //dummy = dummy+'0';



        uart0_putc(dummy & (0xff));

    for (LCD = 0; LCD < 10000; ++LCD) {

            }

        while((spi_is_busy()))
        {
        }
    spi_write(set_pwm_1, dummy);

//    INT16U dummy1 = SSI2_SR_R & (0b10000);
//        if (dummy1 == 0) {
//            SSI2_DR_R = dummy;
//
//        }



    }




}
}

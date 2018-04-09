/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: SPI.c
*
* PROJECT....: Container
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
* 29. mar. 2018 CREATED 
*****************************************************************************/

/***************************** Include files *******************************/
#include "SPI.h"
#include "emp_type.h"
#include "t_model.h"
#include "queue.h"
#include "messages.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>



/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void spi_send_and_receive(void)
{

switch (get_msg_state(SSB_SPI_mode)) {
    case T_SPI_IDLE:
        if (!(queue_is_empty(SQ_SEND_TO_SLAVE))) {

        }

        break;
    case T_SPI_READ:


        break;
    case T_SPI_WRITE:

        break;
    default:
        break;
}
}



INT8U spi_send_lower(message)
INT8U message;
{
    INT8U returnvalue = 0;
    INT8U i;
    INT8U lower_byte  = message;
    INT8U upper_byte  = 0;
    INT8U bitvalue;

    if (!(queue_get_lower_byte(SQ_SEND_TO_SLAVE))) { // hvis nederste byte i SQ_SEND_TO_SLAVE ikke er fyldt i forvejen, indsættes egen byte

            upper_byte = queue_get_upper_byte(SQ_SEND_TO_SLAVE);
            queue_clear_all(SQ_SEND_TO_SLAVE);
            bitvalue = 128;
            for (i = 0; i < 8; ++i) {
                if (lower_byte >= bitvalue) {
                    queue_put(SQ_SEND_TO_SLAVE, 1);
                    lower_byte = lower_byte - bitvalue;
                }
                else {
                    queue_put(SQ_SEND_TO_SLAVE, 0);
                }
                bitvalue = bitvalue / 2;
            }
            bitvalue = 128;
            for (i = 0; i < 8; ++i) {
                if (upper_byte >= bitvalue) {
                    queue_put(SQ_SEND_TO_SLAVE, 1);
                    upper_byte = upper_byte - bitvalue;
                }
                else {
                     queue_put(SQ_SEND_TO_SLAVE, 0);
                }
                bitvalue = bitvalue / 2;
            }

            returnvalue = 1;
        }


return returnvalue;
}

INT8U spi_send_upper(message)
INT8U message;
{
    INT8U returnvalue = 0;
    INT8U i;
    INT8U lower_byte  = 0;
    INT8U upper_byte  = message;
    INT8U bitvalue;

    if (!(queue_get_upper_byte(SQ_SEND_TO_SLAVE))) { // hvis øverste byte i SQ_SEND_TO_SLAVE ikke er fyldt i forvejen, indsættes egen byte

        lower_byte = queue_get_lower_byte(SQ_SEND_TO_SLAVE);
        queue_clear_all(SQ_SEND_TO_SLAVE);
        bitvalue = 128;
        for (i = 0; i < 8; ++i) {
            if (lower_byte >= bitvalue) {
                queue_put(SQ_SEND_TO_SLAVE, 1);
                lower_byte = lower_byte - bitvalue;
            }
            else {
                queue_put(SQ_SEND_TO_SLAVE, 0);
            }
            bitvalue = bitvalue / 2;
        }
        bitvalue = 128;
        for (i = 0; i < 8; ++i) {
            if (upper_byte >= bitvalue) {
                queue_put(SQ_SEND_TO_SLAVE, 1);
                upper_byte = upper_byte - bitvalue;
            }
            else {
                 queue_put(SQ_SEND_TO_SLAVE, 0);
            }
            bitvalue = bitvalue / 2;
        }

        returnvalue = 1;
    }


    return returnvalue;
}

INT8U spi_read_lower(void)
{
    INT8U returnvalue = 0;
    returnvalue = queue_get_lower_byte(SQ_RECEIVED_FROM_SLAVE);

    return returnvalue;
}

INT8U spi_read_upper(void)
{

    INT8U returnvalue = 0;
    returnvalue = queue_get_upper_byte(SQ_RECEIVED_FROM_SLAVE);

    return returnvalue;
}

void spi_init(void)
{
    INT8U dummy = 0;
   // put_msg_state(SSB_SPI_mode, T_SPI_IDLE); // my own stuff

// To enable and initialize the SSI, the following steps are necessary:
// 1. Enable the SSI module using the RCGCSSI register (see page 345).
            SYSCTL_RCGCSSI_R |= (1<<2); // module 2
            dummy++;
            dummy++;
            dummy++;
// 2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register (see page 339).
// To find out which GPIO port to enable, refer to Table 23-5 on page 1346.
            SYSCTL_RCGCGPIO_R |= (1<<1); // port b
// 3. Set the GPIO AFSEL bits for the appropriate pins (see page 669). To determine which GPIOs to
// configure, see Table 23-4 on page 1339.
            //GPIO_PORTB_AFSEL_R |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
            GPIO_PORTB_AFSEL_R |= (0b1111<<4);
//    4. Configure the PMCn fields in the GPIOPCTL register to assign the SSI signals to the appropriate
//    pins. See page 686 and Table 23-5 on page 1346.
            GPIO_PORTB_PCTL_R |= (2<<16) | (2<<20) | (2<<24) | (2<<28);
//    5. Program the GPIODEN register to enable the pin's digital function. In addition, the drive strength,
//    drain select and pull-up/pull-down functions must be configured. Refer to “General-Purpose
//    Input/Outputs (GPIOs)” on page 648 for more information.
            //GPIO_PORTB_DEN_R |= (1<<4) | (1<<5) | (1<<6) | (1<<7);
            GPIO_PORTB_DEN_R|= (0b1111<<4);
//    Note: Pull-ups can be used to avoid unnecessary toggles on the SSI pins which can take the
//    slave to a wrong state.
            GPIO_PORTB_DIR_R |= (1<<4) | (1<<5) | (1<<7);
            GPIO_PORTB_DIR_R &= ~(1<<6);

            GPIO_PORTB_DR2R_R |= (1<<4) | (1<<5) | (1<<7);

            GPIO_PORTB_PUR_R |= (1<<4) | (1<<5) | (1<<7);

            GPIO_PORTB_PUR_R |= (1<<6);

//            For each of the frame formats, the SSI is configured using the following steps:
//            1. Ensure that the SSE bit in the SSICR1 register is clear before making any configuration changes.
            SSI2_CR1_R &= ~(1<<1);
//            2. Select whether the SSI is a master or slave:
//            a. For master operations, set the SSICR1 register to 0x0000.0000.

//            b. For slave mode (output enabled), set the SSICR1 register to 0x0000.0004.
//            c. For slave mode (output disabled), set the SSICR1 register to 0x0000.000C.
//            3. Configure the SSI clock source by writing to the SSICC register.
            SSI2_CC_R &= ~(0x0);
//            4. Configure the clock prescale divisor by writing the SSICPSR register.
            SSI2_CPSR_R = (16<<0); //16
//5. Write the SSICR0 register with the following configuration:

// Serial clock rate (SCR)
//
//            Desired clock phase/polarity, if using Freescale SPI mode (SPH and SPO)
//            The protocol mode: Freescale SPI, TI SSF, MICROWIRE (FRF)
//            The data size (DSS)
            SSI2_CR0_R |= (0xF<<0) | (1<<7);


//            SSI2_CR1_R |= (1<<1);

          //  SSI2_CR1_R &= ~(0b1);
            SSI2_CR1_R |= (1<<1);

            spi_write(options_pwm_1, (1<<8)|(48)); //enable PWM, 1kHz
            while(spi_is_busy()){}
}


INT8U spi_write(command,data)
INT16U data;
INT8U command;
{
    INT8U returnvalue = 0;
    INT8U dummy = 0;
   data = (0x0FFF & data) | (command<<12);
    //dummy = SSI2_SR_R & (1<<4);
    dummy = SSI2_SR_R & (0b10000);
    if (dummy == 0) {
        SSI2_DR_R = data;
        returnvalue = 1;
    }

return returnvalue;
}


INT16U spi_read(void)
{
    INT16U dummy;

    dummy = SSI2_DR_R;
        return dummy;

}

BOOLEAN spi_is_busy(void)
{
    return(SSI2_SR_R & (0b10000));

}

BOOLEAN spi_data_rdy(void)
{
    return(SSI2_SR_R & (1<<2));
}


/****************************** End Of Module *******************************/

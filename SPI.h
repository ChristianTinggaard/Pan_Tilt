/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: SPI.h
*
* PROJECT....: Container
*
* DESCRIPTION: 
* https://www.youtube.com/watch?v=VprofC5ssi4
*
* Change Log:
*****************************************************************************/

#ifndef SPI_H_
#define SPI_H_	

/***************************** Include files *******************************/
#include "emp_type.h"
#include "t_model.h"
/*****************************    Defines    *******************************/
#define set_pwm_1           0b0001
#define options_pwm_1       0b0010
#define set_pwm_2           0b0101
#define options_pwm_2       0b0110
#define get_encoder_1       0b1000
#define options_encoder_1   0b1001
#define get_encoder_2       0b1010
#define options_encoder_2   0b1011
#define get_endestop        0b0111


/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

void spi_send_and_receive(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

INT8U spi_send_lower(INT8U);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

INT8U spi_send_upper(INT8U);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

INT8U spi_read_lower(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

INT8U spi_read_upper(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

void spi_init(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

INT16U spi_read(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

INT8U spi_write(INT8U,INT16U);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

BOOLEAN spi_is_busy(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

BOOLEAN spi_data_rdy(void);
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

/****************************** End Of Module *******************************/
#endif /* SPI_H_ */

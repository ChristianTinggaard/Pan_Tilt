/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: queue.h
*
* PROJECT....: Container
*
* DESCRIPTION: 
*
* Change Log:
*****************************************************************************/

#ifndef QUEUE_H_
#define QUEUE_H_	

/***************************** Include files *******************************/
#include "emp_type.h"

/*****************************    Defines    *******************************/


/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/
void queue_init(void);

INT8U queue_get(INT8U);

INT8U queue_put(INT8U,INT8U);

INT8U queue_get_upper_byte(INT8U); //disse funktioner bruges udelukkende til SPI da queuen altid vil være fyldt ud, yderligere kan disse kun bruges efter 16 shifts bit shifts.

INT8U queue_get_lower_byte(INT8U); //

void queue_clear_all(INT8U);

INT8U queue_is_empty(INT8U);



/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/

/****************************** End Of Module *******************************/
#endif /* QUEUE_H_ */

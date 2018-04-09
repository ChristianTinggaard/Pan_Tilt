/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: t_model.h
*
* PROJECT....: Ass03
*
* DESCRIPTION: 
*
* Change Log:
* Mar 15, 2018 CREATED
*****************************************************************************/

#ifndef T_MODEL_H_
#define T_MODEL_H_	

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

// tasks
#define T_SPI_WRITE                 51
#define T_SPI_READ                  52
#define T_SPI_IDLE                  53



// Shared state buffer
#define SSB_SPI_mode              53

// Shared event buffer


// Watch modes

// Software timers


// Shared Queues

#define SQ_PENDING_FROM_SLAVE       1
#define SQ_PENDING_TO_SLAVE         2
#define SQ_RECEIVED_FROM_SLAVE      3
#define SQ_SEND_TO_SLAVE            4

/********************** External declaration of Variables ******************/

/*****************************   Constants   *******************************/

/*************************  Function interfaces ****************************/

/****************************** End Of Module *******************************/
#endif /* T_MODEL_H_ */

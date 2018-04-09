/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: queue.c
*
* PROJECT....: Container
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
* 29. mar. 2018 CREATED 
*****************************************************************************/

/***************************** Include files *******************************/
#include "queue.h"
#include "emp_type.h"

/*****************************    Defines    *******************************/

#define MAX_QUEUES 8
#define MAX_QUEUE_LENGTH 16

typedef struct queue_descriptor
{
    INT8U length;
    INT8U head;
    INT8U tail;
    INT8U queue_contents[MAX_QUEUE_LENGTH];
} queue_descriptor;




/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
queue_descriptor POQ[MAX_QUEUES]; // Pool of queues

/*****************************   Functions   *******************************/

void queue_init(void)
{
    INT8U i;
    for (i = 0; i < MAX_QUEUES; ++i) {
        POQ[i].head     =   0;
        POQ[i].length   =   0;
        POQ[i].tail     =   0;
    }

}

INT8U queue_get(queuenumber)
INT8U queuenumber;
{
    INT8U returnvalue = 0;
    if (POQ[queuenumber].length) {  // if queue is not empty get value

        returnvalue = POQ[queuenumber].queue_contents[POQ[queuenumber].tail];

        if (POQ[queuenumber].tail == MAX_QUEUE_LENGTH - 1) {
            POQ[queuenumber].tail = 0;
        }
        else {
            POQ[queuenumber].tail = POQ[queuenumber].tail + 1;
        }
        POQ[queuenumber].length = POQ[queuenumber].length -1;
    }
    else {     // else do nothing


    }
    return returnvalue;
}



INT8U queue_put(queuenumber, item)
INT8U queuenumber;
INT8U item;
{
    INT8U returnvalue = 0;
    if (POQ[queuenumber].length != MAX_QUEUE_LENGTH) { // if queue is not full, put item

        POQ[queuenumber].queue_contents[POQ[queuenumber].head]=item;
            if ((POQ[queuenumber].head) == (MAX_QUEUE_LENGTH-1)) {
                POQ[queuenumber].head=0;
            }
            else {
                POQ[queuenumber].head = POQ[queuenumber].head +1;
            }
            POQ[queuenumber].length = POQ[queuenumber].length +1;
            returnvalue = 1;
    }

    return returnvalue;
}

INT8U queue_get_upper_byte(queuenumber)
INT8U queuenumber;
{
    INT8U i;
    INT8U bit_value = 1;
    INT8U returnvalue = 0;
    for (i = 0; i < 8; ++i) {
        returnvalue += (bit_value * (POQ[queuenumber].queue_contents[i+8]));
        bit_value = bit_value * 2;
    }
    return returnvalue;
}


INT8U queue_get_lower_byte(queuenumber)
INT8U queuenumber;
{
    INT8U i;
    INT8U bit_value = 1;
    INT8U returnvalue = 0;
    for (i = 0; i < 8; ++i) {
            returnvalue += (bit_value * (POQ[queuenumber].queue_contents[i]));
            bit_value = bit_value * 2;
    }
    return returnvalue;
}

void queue_clear_all(queuenumber)
INT8U queuenumber;
{
    INT8U i;
    for (i = 0; i < MAX_QUEUE_LENGTH; ++i) {
        POQ[queuenumber].queue_contents[i] = 0;
    }

    POQ[queuenumber].head = 0;
    POQ[queuenumber].tail = 0;
    POQ[queuenumber].length = 0;

}


INT8U queue_is_empty(queuenumber)
INT8U queuenumber;
{
    INT8U returnvalue = 0;
    if (POQ[queuenumber].length == 0) { // hvis længden er nul, ændres returværdien til 1 ellers returneres 0
        returnvalue = 1;
    }

    return returnvalue;
}

/****************************** End Of Module *******************************/

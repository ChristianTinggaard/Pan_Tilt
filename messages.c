/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: messages.c
*
* PROJECT....: Ass03
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
* Mar 15, 2018 CREATED 
*****************************************************************************/

/***************************** Include files *******************************/
#include "messages.h"
/*****************************    Defines    *******************************/

#define MAX_MSG 64

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U msg_event[MAX_MSG];
INT8U msg_state[MAX_MSG];

/*****************************   Functions   *******************************/

INT8U get_msg_event( INT8U event_name )
{
    INT8U result = 0;

    if ( event_name < MAX_MSG)
    {
        if ( msg_event[event_name] )
        {
            result = msg_event[event_name];
            msg_event[event_name] = 0;
        }
    }

    return result;
}

void put_msg_event( INT8U event_name, INT8U event_type)
{
    if (event_name < MAX_MSG)
        msg_event[event_name] = event_type;
}

INT8U get_msg_state( INT8U state_name )
{
    INT8U result = 0;

    if( state_name < MAX_MSG )
    {
        result = msg_state[state_name];
    }
    return result;
}

void put_msg_state( INT8U state_name, INT8U state_type )
{
    if( state_name < MAX_MSG )
    {
        msg_state[state_name] = state_type;
    }
}

/****************************** End Of Module *******************************/



/*	Author: Edward Zhu
 *	 *	 *	 *  Partner(s) Name: 
 *	  *	  *	  *	Lab Section:
 *	   *	   *	   *	Assignment: Lab 4  Exercise 4
 *	    *	    *	    *	Exercise Description: [optional - include for your own benefit]
 *	     *	     *	     *
 *	      *	      *	      *	I acknowledge all content contained herein, excluding template or example
 *	       *	       *	       *	code, is my own original work.
 *	        *	        *	        */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum DOOR_STATES
{
    DOOR_START,
    BUTTON_PRESS,
    DOOR_WAIT,
} DOOR_STATE;
unsigned char count = 0;
unsigned char arr[4] = {0,0,0,0};
int i = 0;

void DOOR_SM()
{
    switch (DOOR_STATE)
    {
    case DOOR_START:
        if (PINA != 0)
        {
            arr[count++] = PINA;
            DOOR_STATE = BUTTON_PRESS;
        }
        break;
    case BUTTON_PRESS:
        if (PINA != 0)
        {
            DOOR_STATE = BUTTON_PRESS;
        }
        else
        {
            DOOR_STATE = DOOR_WAIT;
        }
        break;
    case DOOR_WAIT:
        if (PINA == 0)
        {
            DOOR_STATE = DOOR_WAIT;
        }
        else
        {
            arr[count++] = PINA;
            if (count == 4)
            {
                if (arr[0] == 0x04 && arr[1] == 0x01 && arr[2] == 0x02 && arr[3] == 0x01)
                {
                    PORTB = 1;
                }
                else
                {
                    PORTB = 0;
                }
            }
            DOOR_STATE = BUTTON_PRESS;
        }
    }

    switch (DOOR_STATE)
    {
    case BUTTON_PRESS:
        break;
    default:
        break;
    }
}

int main(void)
{
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;
    DOOR_STATE = DOOR_START;
    while (1)
    {
        DOOR_SM();
    }
}

//{'inputs' : [('PINA', 0x00)], 'iterations' : 3},
//// {'inputs' : [('PINA', 0x01)], 'iterations' : 2},
//// {'inputs' : [('PINA', 0x00)], 'iterations' : 3},
//// {'inputs' : [('PINA', 0x02)], 'iterations' : 2},
//// {'inputs' : [('PINA', 0x00)], 'iterations' : 2},
//// {'inputs' : [('PINA', 0x01)], 'iterations' : 2},
//


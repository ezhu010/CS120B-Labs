
/*	Author: Edward Zhu
 *	 *	 *  Partner(s) Name: 
 *	  *	  *	Lab Section:
 *	   *	   *	Assignment: Lab 4  Exercise 4
 *	    *	    *	Exercise Description: [optional - include for your own benefit]
 *	     *	     *
 *	      *	      *	I acknowledge all content contained herein, excluding template or example
 *	       *	       *	code, is my own original work.
 *	        *	        */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum DOOR_STATES
{
    DOOR_START,
    DOOR_LOCK,
    DOOR_UNLOCK,
    DOOR_BUTTONP,
    DOOR_WAIT,
} DOOR_STATE;
unsigned char count = 0;
unsigned char arr[4];
int i = 0;

void DOOR_SM()
{
    switch (DOOR_STATE)
    {
    case DOOR_START:
        if (PINA != 0x00)
        {
            arr[count] = PINA;
            count++;
            DOOR_STATE = DOOR_BUTTONP;
        }

    case DOOR_BUTTONP:
        if (PINA != 0)
        {
            DOOR_STATE = DOOR_BUTTONP;
        }
	if(count == 4){
	    PORTB = 0x01;
	}
        else
        {
            DOOR_STATE = DOOR_WAIT;
        }

    case DOOR_WAIT:
        if (PINA == 0)
        {
            DOOR_STATE = DOOR_WAIT;
        }
        if (count == 4)
        {
            if (arr[0] == 0x04 && arr[1] == 0x01 && arr[2] == 0x02 && arr[3] == 0x01)
            {
                PORTB = 0x01;
            }
        }
        else
        {
            arr[count] = PINA;
            count++;
            DOOR_STATE = DOOR_BUTTONP;
        }
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



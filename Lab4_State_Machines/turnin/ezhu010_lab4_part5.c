/*	Author: Edward Zhu
 *	 *  Partner(s) Name: 
 *	  *	Lab Section:
 *	   *	Assignment: Lab 4  Exercise 5
 *	    *	Exercise Description: [optional - include for your own benefit]
 *	     *
 *	      *	I acknowledge all content contained herein, excluding template or example
 *	       *	code, is my own original work.
 *	        */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
int count = 0;
int i = 0;
int arr[] = {};
enum DOOR_STATE
{
    DOOR_START,
    DOOR_LOCK,
    DOOR_UNLOCK,
    DOOR_PASS,
    DOOR_WAIT,
} DOOR_STATE;

void DOOR_SM()
{
    switch (DOOR_STATE)
    {
    case DOOR_START:
        DOOR_STATE = DOOR_LOCK;
        break;

    case DOOR_LOCK:
        if (PINA == 0x00)
        {
            DOOR_STATE = DOOR_LOCK;
        }
        else if (PINA == 0x80)
        {
            DOOR_STATE = DOOR_LOCK;
        }
        else if (PINA != 0x00)
        {
            DOOR_STATE = DOOR_PASS;
        }
        break;

    case DOOR_PASS:
        if (count < 4)
        {
            DOOR_STATE = DOOR_PASS;
        }
        if (PINA == 0x00)
        {
            DOOR_STATE = DOOR_WAIT;
        }
        else if (PORTB == 0x00)
        {
            if (arr[0] == 0x04 && arr[1] == 0x01 && arr[2] == 0x02 && arr[3] == 0x01)
            {
                DOOR_STATE = DOOR_UNLOCK;
            }
            else
            {
                DOOR_STATE = DOOR_LOCK;
            }
        }
        else if (PORTB == 0x01)
        {
            if (arr[0] == 0x04 && arr[1] == 0x01 && arr[2] == 0x02 && arr[3] == 0x01)
            {
                DOOR_STATE = DOOR_LOCK;
            }
            else
            {
                DOOR_STATE = DOOR_UNLOCK;
            }
        }
        break;

    case DOOR_UNLOCK:
        if (PINA == 0x00)
        {
            DOOR_STATE = DOOR_UNLOCK;
        }
        else if (PINA == 0x80)
        {
            DOOR_STATE = DOOR_LOCK;
        }
        else if (PINA != 0x00)
        {
            DOOR_STATE = DOOR_PASS;
        }
        break;

        case DOOR_WAIT:
            break;
    }

    switch (DOOR_STATE)
    {
    case DOOR_START:
            PORTB = 0x00;
            break;
        case DOOR_LOCK:
            PORTB = 0x00;
            for (i = 0; i < 4; i++)
            {
                arr[i] = 0;
            }
            count = 0;
            break;

        case DOOR_PASS:
            arr[count] = PINA;
            count++;
            break;

        case DOOR_UNLOCK:
            PORTB = 0x01;
            for (i = 0; i < 4; i++)
            {
                arr[i] = 0;
            }
            count = 0;
            break;

        case DOOR_WAIT:
            break;
        }
}

int main()
{
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;
    while (1)
    {
        DOOR_SM();
    }
    return 1;
}

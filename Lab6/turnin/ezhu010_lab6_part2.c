/* Author: Edward Zhu
 * Lab Section: 023
 * Assignment: Lab 6  Exercise 2
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code is my own original work.
 *
 *  Demo Link: https://youtu.be/8DbNuU8Klhs
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"
enum LIGHT_STATES
{
	LIGHT_START,
	LIGHT_INIT,
	LIGHT_NEXT,
	LIGHT_PAUSE,
	LIGHT_RESET_ONE,
	LIGHT_RESET_TWO
} LIGHT_STATE;
unsigned char temp = 0x00;

void LIGHT_SM()
{
	switch (LIGHT_STATE)
	{
	case LIGHT_START:
		LIGHT_STATE = LIGHT_INIT;
		break;
	case LIGHT_INIT:
		LIGHT_STATE = LIGHT_NEXT;
		break;
	case LIGHT_NEXT:
		if (~PINA & 0x01)
		{
			LIGHT_STATE = LIGHT_PAUSE;
		}
		else
		{
			LIGHT_STATE = LIGHT_NEXT;
		}
		break;
	case LIGHT_PAUSE:
		if (~PINA & 0x01)
		{
			LIGHT_STATE = LIGHT_PAUSE;
		}
		else
		{
			LIGHT_STATE = LIGHT_RESET_ONE;
		}
		break;
	case LIGHT_RESET_ONE:
		if (~PINA & 0x01)
		{
			LIGHT_STATE = LIGHT_RESET_TWO;
		}
		else
		{
			LIGHT_STATE = LIGHT_RESET_ONE;
		}
		break;
	case LIGHT_RESET_TWO:
		if (~PINA & 0x01)
		{
			LIGHT_STATE = LIGHT_RESET_TWO;
		}
		else
		{
			LIGHT_STATE = LIGHT_INIT;
		}
		break;
	default:
		LIGHT_STATE = LIGHT_START;
		break;
	}
	switch (LIGHT_STATE)
	{
	case LIGHT_START:
		break;
	case LIGHT_INIT:
		PORTB = 0x01;
		break;
	case LIGHT_NEXT:
		if (temp == 0x00)
		{
			if (PORTB == 0x04)
			{
				PORTB = PORTB >> 1;
				temp = 0x01;
			}
			else
			{
				PORTB = PORTB << 1;
			}
		}
		else
		{
			if (PORTB == 0x01)
			{
				PORTB = PORTB << 1;
				temp = 0x00;
			}
			else
			{
				PORTB = PORTB >> 1;
			}
		}
		break;
	case LIGHT_PAUSE:
		break;
	case LIGHT_RESET_ONE:
		break;
	case LIGHT_RESET_TWO:
		break;
	default:
		break;
	}
}

int main()
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	while (1)
	{
		LIGHT_SM();
		while (!TimerFlag)
			;
		TimerFlag = 0;
	}
}

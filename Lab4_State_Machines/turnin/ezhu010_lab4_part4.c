/*	Author: Edward Zhu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum DOOR_STATE
{
	DOOR_START,
	DOOR_LOCK,
	DOOR_UNLOCK_ONE,
	DOOR_WAIT_ONE,
	DOOR_UNLOCK_TWO,
	DOOR_WAIT_TWO,
	DOOR_LOCK_ONE,
	DOOR_LOCK_WAIT_ONE,
} DOOR_STATE;

void DOOR_SM()
{
	switch (DOOR_STATE)
	{
	case DOOR_START:
		DOOR_STATE = DOOR_LOCK;
		break;

	case DOOR_LOCK:
		if (PINA == 0x04)
		{
			DOOR_STATE = DOOR_UNLOCK_ONE;
		}
		else
		{
			DOOR_STATE = DOOR_LOCK;
		}
		break;

	case DOOR_UNLOCK_ONE:
		if (PINA == 0x04)
		{
			DOOR_STATE = DOOR_UNLOCK_ONE;
		}
		else if (PINA == 0x00)
		{
			DOOR_STATE = DOOR_WAIT_ONE;
		}
		else
		{
			DOOR_STATE = DOOR_LOCK;
		}
		break;

	case DOOR_WAIT_ONE:
		if (PINA == 0x00)
		{
			DOOR_STATE = DOOR_WAIT_ONE;
		}
		else if (PINA == 0x02)
		{
			DOOR_STATE = DOOR_UNLOCK_TWO;
		}
		else
		{
			DOOR_STATE = DOOR_LOCK;
		}
		break;

	case DOOR_UNLOCK_TWO:
		if (PINA == 0x02)
		{
			DOOR_STATE = DOOR_UNLOCK_TWO;
		}
		else if (PINA == 0x00)
		{
			DOOR_STATE = DOOR_WAIT_TWO;
		}
		break;

	case DOOR_WAIT_TWO:
		if (PINA == 0x80)
		{
			DOOR_STATE = DOOR_LOCK;
		}
		else if (PINA == 0x00)
		{
			DOOR_STATE = DOOR_WAIT_TWO;
		}
		else if (PINA == 0x04)
		{
			DOOR_STATE = DOOR_LOCK_ONE;
		}
		break;

	case DOOR_LOCK_ONE:
		if (PINA == 0x04)
		{
			DOOR_STATE = DOOR_LOCK_ONE;
		}
		else if (PINA == 0x80)
		{
			DOOR_STATE = DOOR_LOCK;
		}
		else if (PINA == 0x00)
		{
			DOOR_STATE = DOOR_LOCK_WAIT_ONE;
		}
		break;

	case DOOR_LOCK_WAIT_ONE:
		if (PINA == 0x00)
		{
			DOOR_STATE = DOOR_LOCK_WAIT_ONE;
		}
		else if (PINA == 0x02)
		{
			DOOR_STATE = DOOR_LOCK;
		}
		else if (PINA == 0x80)
		{
			DOOR_STATE = DOOR_LOCK;
		}
		else
		{
			DOOR_STATE = DOOR_WAIT_TWO;
		}
	}

	switch (DOOR_STATE)
	{
	case DOOR_START:
		PORTB = 0x00;
		break;
	case DOOR_LOCK:
		PORTB = 0x00;
		break;
	case DOOR_UNLOCK_ONE:
		break;
	case DOOR_WAIT_ONE:
		break;
	case DOOR_UNLOCK_TWO:
		PORTB = 0x01;
	case DOOR_WAIT_TWO:
		break;
	case DOOR_LOCK_WAIT_ONE:
		break;
	case DOOR_LOCK_ONE:
		break;
	}
}

int main(void)
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

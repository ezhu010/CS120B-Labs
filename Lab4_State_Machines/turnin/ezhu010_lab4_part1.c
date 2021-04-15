/*	Author: Edward Zhu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LED_STATES
{
	LED_START,
	LED_LIGHT_ONE,
	LED_LIGHT_TWO,
	LED_WAIT_ONE,
	LED_WAIT_TWO
} LED_STATES;

void LED_SM()
{

	switch (LED_STATES)
	{
	case LED_START:
		LED_STATES = LED_LIGHT_ONE;
		break;

	case LED_LIGHT_ONE:
		if (PINA == 0x00)
		{
			LED_STATES = LED_LIGHT_ONE;
		}
		if (PINA == 0x01)
		{
			LED_STATES = LED_WAIT_ONE;
		}
		break;

	case LED_WAIT_ONE:
		if (PINA == 0x01)
		{
			LED_STATES = LED_WAIT_ONE;
		}
		if (PINA == 0x00)
		{
			LED_STATES = LED_LIGHT_TWO;
		}
		break;

	case LED_WAIT_TWO:
		if (PINA == 0x00)
		{
			LED_STATES = LED_LIGHT_ONE;
		}
		if (PINA == 0x01)
		{
			LED_STATES = LED_WAIT_TWO;
		}
		break;

	case LED_LIGHT_TWO:
		if (PINA == 0x00)
		{
			LED_STATES = LED_LIGHT_TWO;
		}
		if (PINA == 0x01)
		{
			LED_STATES = LED_WAIT_TWO;
		}
		break;

	default:
		LED_STATES = LED_START;
		break;
	}

	switch (LED_STATES)
	{
	case LED_START:
		PORTB = 0x01;
		break;
	case LED_LIGHT_ONE:
		PORTB = 0x01;
		break;
	case LED_WAIT_ONE:
		PORTB = 0x02;
		break;
	case LED_WAIT_TWO:
		PORTB = 0x01;
		break;

	case LED_LIGHT_TWO:
		PORTB = 0x02;
		break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0x00;
	DDRB = 0xFF;
	PORTB = 0X00;
	LED_STATES = LED_START;
	while (1)
	{
		LED_SM();
	}

	return 1;
}

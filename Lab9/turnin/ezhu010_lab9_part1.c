
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"
enum ThreeLEDStates
{
	ThreeStart,
	Zero,
	One,
	Two
} ThreeLEDstate;
enum BlinkingLEDStates
{
	BlinkingStart,
	BlinkingInit,
	Blink
} BlinkingLEDstate;
enum CombineLEDStates
{
	CombineStart,
	CombineInit
} CombineLEDstate;
unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;

void TickThreeLEDsSM()
{
	switch (ThreeLEDstate)
	{
	case ThreeStart:
		ThreeLEDstate = Zero;
		break;

	case Zero:
		ThreeLEDstate = One;
		break;

	case One:
		ThreeLEDstate = Two;
		break;

	case Two:
		ThreeLEDstate = Zero;
		break;

	default:
		ThreeLEDstate = ThreeStart;
		break;
	}

	switch (ThreeLEDstate)
	{
	case ThreeStart:
		break;
	case Zero:
		threeLEDs = 0x01;
		break;
	case One:
		threeLEDs = 0x02;
		break;
	case Two:
		threeLEDs = 0x04;
		break;
	default:
		break;
	}
}

void TickBlinkingLEDSM()
{
	switch (BlinkingLEDstate)
	{
	case BlinkingStart:
		BlinkingLEDstate = BlinkingInit;
		break;
	case BlinkingInit:
		BlinkingLEDstate = Blink;
		break;
	case Blink:
		BlinkingLEDstate = BlinkingInit;
		break;
	default:
		BlinkingLEDstate = BlinkingStart;
		break;
	}
	switch (BlinkingLEDstate)
	{
	case BlinkingStart:
		break;
	case BlinkingInit:
		blinkingLED = 0x00;
		break;
	case Blink:
		blinkingLED = 0x01;
		break;
	default:
		break;
	}
}

void TickCombineLEDsSM()
{
	switch (CombineLEDstate)
	{
	case CombineStart:
		CombineLEDstate = CombineInit;
		break;
	case CombineInit:
		CombineLEDstate = CombineInit;
		break;
	default:
		CombineLEDstate = CombineStart;
		break;
	}
	switch (CombineLEDstate)
	{
	case CombineStart:
		break;
	case CombineInit:
		PORTB = ((blinkingLED << 3) | (threeLEDs));
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
	unsigned long elapsed = 0;
	const unsigned long timerPeriod = 1000;
	TimerSet(1000);
	TimerOn();
	ThreeLEDstate = ThreeStart;
	BlinkingLEDstate = BlinkingStart;
	CombineLEDstate = CombineStart;

	while (1)
	{
		TickThreeLEDsSM();
		TickBlinkingLEDSM();
		TickCombineLEDsSM();
		while (!TimerFlag)
		{
		};
		TimerFlag = 0;
	}
	return 0;
}

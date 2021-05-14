
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"
enum ThreeLightStates
{
	LIGHT_ZERO,
	LIGHT_ONE,
	LIGHT_TWO
} ThreeLightState;
enum BlinkLightStates
{
	LIGHT_INIT,
	LIGHT_BLINK
} BlinkLightState;

enum SPEAKER_STATES
{
	SPEAKER_OFF,
	SPEAKER_ON,
	SPEAKER_INCRE_FREQ,
	SPEAKER_DECRE_FREQ,
	SPEAKER_RELEASE,
} SPEAKER_STATE;

enum CombineLightStates
{
	COMBINE_INIT
} CombineLightState;

unsigned char threeLEDs = 0;
unsigned char blinkingLED = 0;
unsigned char temp = 0x00;
unsigned char sound = 0;
unsigned char sounds[] = {1, 2, 3, 4, 5, 6};
unsigned char temp2 = 0;

void ThreeLEDsSM()
{
	switch (ThreeLightState)
	{

	case LIGHT_ZERO:
		ThreeLightState = LIGHT_ONE;
		break;
	case LIGHT_ONE:
		ThreeLightState = LIGHT_TWO;
		break;

	case LIGHT_TWO:
		ThreeLightState = LIGHT_ZERO;
		break;
	}

	switch (ThreeLightState)
	{

	case LIGHT_ZERO:
		threeLEDs = 0x01;
		break;
	case LIGHT_ONE:
		threeLEDs = 0x02;
		break;
	case LIGHT_TWO:
		threeLEDs = 0x04;
		break;
	default:
		break;
	}
}

void BlinkingLEDSM()
{
	switch (BlinkLightState)
	{
	case LIGHT_INIT:
		BlinkLightState = LIGHT_BLINK;
		break;
	case LIGHT_BLINK:
		BlinkLightState = LIGHT_INIT;
		break;
	}
	switch (BlinkLightState)
	{
	case LIGHT_INIT:
		blinkingLED = 0x00;
		break;
	case LIGHT_BLINK:
		blinkingLED = 0x01;
		break;
	default:
		break;
	}
}

void SPEAKER_SM()
{
	switch (SPEAKER_STATE)
	{
	case SPEAKER_OFF:
		if ((~PINA & 0x07) == 0x04)
		{
			SPEAKER_STATE = SPEAKER_ON;
		}
		else if ((~PINA & 0x07) == 0x01)
		{
			SPEAKER_STATE = SPEAKER_INCRE_FREQ;
		}
		else if ((~PINA & 0x07) == 0x02)
		{
			SPEAKER_STATE = SPEAKER_DECRE_FREQ;
		}
		else
		{
			SPEAKER_STATE = SPEAKER_OFF;
		}
		break;

	case SPEAKER_ON:
		if ((~PINA & 0x07) == 0x00)
		{
			SPEAKER_STATE = SPEAKER_OFF;
		}
		else
		{
			SPEAKER_STATE = SPEAKER_ON;
		}
		break;

	case SPEAKER_DECRE_FREQ:
		SPEAKER_STATE = SPEAKER_RELEASE;
		break;

	case SPEAKER_INCRE_FREQ:
		SPEAKER_STATE = SPEAKER_RELEASE;
		break;

	case SPEAKER_RELEASE:
		if ((~PINA & 0x07) == 0x00)
		{
			SPEAKER_STATE = SPEAKER_OFF;
		}
		else
		{
			SPEAKER_STATE = SPEAKER_RELEASE;
		}
		break;
	}
	switch (SPEAKER_STATE)
	{

	case SPEAKER_OFF:
		temp = 0x00;
		sound = 0;
		break;

	case SPEAKER_ON:
		if (sound <= sounds[temp2])
		{
			temp = 0x01;
		}
		else if (sound <= (sounds[j] * 2))
		{
			temp = 0x00;
		}
		else
		{
			sound = 0;
		}
		++sound;
		break;

	case SPEAKER_INCRE_FREQ:
		if (temp2 > 0)
		{
			temp2--;
		}
		break;

	case SPEAKER_DECRE_FREQ:
		if (temp2 < 6)
		{
			temp2++;
		}
		break;
	}
}

void CombineLEDsSM()
{
	PORTB = ((temp << 4) | (blinkingLED << 3) | (threeLEDs));
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	unsigned long ThreeLightTime = 0;
	unsigned long BlinkLightTime = 0;
	const unsigned long period = 1;
	TimerSet(1);
	TimerOn();
	ThreeLightState = LIGHT_ZERO;
	BlinkLightState = LIGHT_INIT;
	SPEAKER_STATE = SPEAKER_OFF;

	while (1)
	{
		if (ThreeLightTime >= 300)
		{
			ThreeLEDsSM();
			ThreeLightTime = 0;
		}
		if (BlinkLightTime >= 1000)
		{
			BlinkingLEDSM();
			BlinkLightTime = 0;
		}
		SPEAKER_SM();
		CombineLEDsSM();
		while (!TimerFlag)
		{
		};
		TimerFlag = 0;
		ThreeLightTime += period;
		BlinkLightTime += period;
	}
	return 0;
}

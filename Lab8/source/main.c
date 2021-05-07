#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

// int notes[15] = {261.33,261.33,392,392,440,440,392, 349.23, 349.23,329.63, 329.63,293.66,293.66,261.33,0};
int notes[32] = {261.33, 0, 261.33,0,392,0,392,0,440,0,440,0,392,0,392,0,349.23,0,349.23,0,329.23,0,329.23,0,293.66,0, 293.66,0,261.33,261.33 ,-1};

void set_PWM(double frequency)
{
	static double current_frequency;
	if (frequency != current_frequency)
	{
		if (!frequency)
		{
			TCCR3B &= 0x08;
		}
		else
		{
			TCCR3B |= 0x03;
		}
		if (frequency < 0.954)
		{
			OCR3A = 0xFFFF;
		}
		else if (frequency > 31250)
		{
			OCR3A = 0x0000;
		}
		else
		{
			OCR3A = (short)(8000000 / (128 * frequency)) - 1;
		}
		TCNT3 = 0;
		current_frequency = frequency;
	}
}
void PWM_on()
{
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}
void PWM_off()
{
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}
int i = 0;
enum SPEAKER
{
	SPEAKER_INIT,
	SPEAKER_PLAY,
	SPEAKER_FINISH
} SPEAKER_STATE;

void SPEAKER_SM()
{
	switch (SPEAKER_STATE)
	{
	case SPEAKER_INIT:
		if ((~PINA & 0x01) == 0x01)
		{
			SPEAKER_STATE = SPEAKER_PLAY;
		}
		else
		{
			SPEAKER_STATE = SPEAKER_INIT;
		}
		break;
	case SPEAKER_PLAY:
		if (notes[i] != -1)
		{
			TimerSet(1000);
			SPEAKER_STATE = SPEAKER_PLAY;
		}
		else if (notes[i] == -1 && (~PINA & 0x01) == 0)
		{
			SPEAKER_STATE = SPEAKER_INIT;
			i = 0;
			TimerSet(100);
		}
		else if (notes[i] == -1 && (~PINA & 0x01) == 0x01)
		{
			i = 0;
			TimerSet(100);
			SPEAKER_STATE = SPEAKER_FINISH;
		}
		break;

	case SPEAKER_FINISH:
		if ((~PINA & 0x01) == 0x01)
		{
			SPEAKER_STATE = SPEAKER_FINISH;
		}
		else
		{
			SPEAKER_STATE = SPEAKER_INIT;
		}
		break;
	}

	switch (SPEAKER_STATE)
	{
	case SPEAKER_INIT:
		set_PWM(0);
		break;
	case SPEAKER_PLAY:
		if(notes[i] != 0){
			TimerSet(500);
		}
		else {
			TimerSet(100);
		}
		set_PWM(notes[i]);
		i++;
		break;

	case SPEAKER_FINISH:
		set_PWM(0);
		break;
	}
}

int main()
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(100);
	PWM_on();
	TimerOn();
	SPEAKER_STATE = SPEAKER_INIT;

	while (1)
	{
		SPEAKER_SM();
		while (!TimerFlag)
		{
		};
		TimerFlag = 0;
	}
}

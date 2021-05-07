/*	Author: Edward Zhu
 *  Partner(s) Name: 
 *	Lab Section: 023
 *	Assignment: Lab 8  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"
enum SPEAKER_STATES
{
    SPEAKER_START,
    SPEAKER_INIT,
    SPEAKER_C,
    SPEAKER_D,
    SPEAKER_E
} SPEAKER_STATE;

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

void SPEAKER_SM()
{
    switch (SPEAKER_STATE)
    {
    case SPEAKER_START:
        SPEAKER_STATE = SPEAKER_INIT;
        break;

    case SPEAKER_INIT:
        if ((~PINA & 0x07) == 0x01)
        {
            SPEAKER_STATE = SPEAKER_C;
        }
        else if ((~PINA & 0x07) == 0x02)
        {
            SPEAKER_STATE = SPEAKER_D;
        }
        else if ((~PINA & 0x07) == 0x04)
        {
            SPEAKER_STATE = SPEAKER_E;
        }
        else
        {
            SPEAKER_STATE = SPEAKER_INIT;
        }
        break;

    case SPEAKER_PLAYC:
        if ((~PINA & 0x07) == 0x01)
        {
            SPEAKER_STATE = SPEAKER_C;
        }
        else
        {
            SPEAKER_STATE = SPEAKER_INIT;
        }
        break;

    case SPEAKER_D:
        if ((~PINA & 0x07) == 0x02)
        {
            SPEAKER_STATE = SPEAKER_D;
        }
        else
        {
            SPEAKER_STATE = SPEAKER_INIT;
        }
        break;

    case SPEAKER_E:
        if ((~PINA & 0x07) == 0x04)
        {
            SPEAKER_STATE = SPEAKER_E;
        }
        else
        {
            SPEAKER_STATE = SPEAKER_INIT;
        }
        break;

    default:
        SPEAKER_STATE = SPEAKER_START;
        break;
    }
    switch (SPEAKER_STATE)
    {
    case SPEAKER_START:
        break;
    case SPEAKER_INIT:
        set_PWM(0);
        break;
    case SPEAKER_C:
        set_PWM(261.63);
        break;
    case SPEAKER_D:
        set_PWM(293.66);
        break;
    case SPEAKER_E:
        set_PWM(329.63);
        break;
    }
}

void main(void)
{
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;
    TimerSet(100);
    PWM_on();

    TimerOn();
    while (1)
    {
        SPEAKER_SM();
        while (!TimerFlag)
        {
        };
        TimerFlag = 0;
    }
}

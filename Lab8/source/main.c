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
#include "io.h"
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"
enum States
{
    Start,
    Init,
    Cnote,
    Dnote,
    Enote
} state;
double temp = 0;
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

void Tick()
{
    switch (state)
    {
    case Start:
        state = Init;
        break;

    case Init:
        if ((~PINA & 0x07) == 0x01)
        {
            state = Cnote;
        }
        else if ((~PINA & 0x07) == 0x02)
        {
            state = Dnote;
        }
        else if ((~PINA & 0x07) == 0x04)
        {
            state = Enote;
        }
        else
        {
            state = Init;
        }
        break;

    case Cnote:
        if ((~PINA & 0x07) == 0x01)
        {
            state = Cnote;
        }
        else
        {
            state = Init;
        }
        break;

    case Dnote:
        if ((~PINA & 0x07) == 0x02)
        {
            state = Dnote;
        }
        else
        {
            state = Init;
        }
        break;

    case Enote:
        if ((~PINA & 0x07) == 0x04)
        {
            state = Enote;
        }
        else
        {
            state = Init;
        }
        break;

    default:
        state = Start;
        break;
    }
    switch (state)
    {
    case Start:
        break;
    case Init:
        set_PWM(0);
        break;
    case Cnote:
        set_PWM(261.63);
        break;
    case Dnote:
        set_PWM(293.66);
        break;
    case Enote:
        set_PWM(329.63);
        break;
    default:
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
    TimerOn();
    PWM_on();
    while (1)
    {
        Tick();
        while (!TimerFlag)
        {
        };
        TimerFlag = 0;
    }
}
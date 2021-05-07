#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum SPEAKER_STATES
{
    SPEAKER_BEGIN,
    SPEAKER_INIT,
    SPEAKER_SCALE_UP,
    SPEAKER_SCALE_DOWN,
    SPEAKER_SOUND,
    SPEAKER_BUTTON
} SPEAKER_STATE;

unsigned char alternate = 0x00;
unsigned char i = 0x00;
double notes[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

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
    case SPEAKER_BEGIN:
        SPEAKER_STATE = SPEAKER_INIT;
        break;

    case SPEAKER_INIT:
        if ((~PINA & 0x07) == 0x01)
        {
            SPEAKER_STATE = SPEAKER_SCALE_UP;
        }
        else if ((~PINA & 0x07) == 0x02)
        {
            SPEAKER_STATE = SPEAKER_SCALE_DOWN;
        }
        else if ((~PINA & 0x07) == 0x04)
        {
            SPEAKER_STATE = SPEAKER_SOUND;
        }
        else
        {
            SPEAKER_STATE = SPEAKER_INIT;
        }
        break;

    case SPEAKER_SCALE_UP:
        SPEAKER_STATE = SPEAKER_BUTTON;
        break;

    case SPEAKER_SCALE_DOWN:
        SPEAKER_STATE = SPEAKER_BUTTON;
        break;

    case SPEAKER_SOUND:
        SPEAKER_STATE = SPEAKER_BUTTON;
        break;

    case SPEAKER_BUTTON:
        if ((~PINA & 0x07) == 0x00)
        {
            SPEAKER_STATE = SPEAKER_INIT;
        }
        else
        {
            SPEAKER_STATE = SPEAKER_BUTTON;
        }
        break;

    default:
        SPEAKER_STATE = SPEAKER_BEGIN;
        break;
    }
    switch (SPEAKER_STATE)
    {
    case SPEAKER_BEGIN:
        break;
    case SPEAKER_INIT:
        break;
    case SPEAKER_SCALE_UP:
        if (i < 0x07)
        {
            ++i;
        }
        if (alternate == 0x01)
        {
            set_PWM(notes[i]);
        }
        break;
    case SPEAKER_SCALE_DOWN:
        if (i > 0x00)
        {
            --i;
        }
        if (alternate == 0x01)
        {
            set_PWM(notes[i]);
        }
        break;
    case SPEAKER_SOUND:
        if (alternate == 0x00)
        {
            alternate = 0x01;
            set_PWM(notes[i]);
        }
        else
        {
            alternate = 0x00;
            set_PWM(0);
        }
        break;
    case SPEAKER_BUTTON:
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
    TimerSet(100);
    TimerOn();
    PWM_on();
    while (1)
    {
        SPEAKER_SM();
        while (!TimerFlag)
        {
        };
        TimerFlag = 0;
    }
    return 0;
}
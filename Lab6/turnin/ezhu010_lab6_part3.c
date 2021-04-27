
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"
enum COUNTER_STATES
{
    COUNTER_START,
    COUNTER_BEGIN,
    COUNTER_INIT,
    COUNTER_RESET,
    COUNTER_INCRE,
    COUNTER_DECRE,
    COUNTER_INCRE_WAIT,
    COUNTER_DECRE_WAIT,
    COUNTER_INCRE_HOLD,
    COUNTER_DECRE_HOLD,
} COUNTER_STATE;
unsigned char temp = 0x00;

void COUNT_SM()
{
    switch (COUNTER_STATE)
    {
    case COUNTER_START:
        COUNTER_STATE = COUNTER_BEGIN;
        break;
    case COUNTER_BEGIN:
        COUNTER_STATE = COUNTER_INIT;
        break;
    case COUNTER_INIT:
        if ((~PINA & 0x03) == 0x03)
        {
            COUNTER_STATE = COUNTER_RESET;
        }
        else if ((~PINA & 0x03) == 0x01)
        {
            COUNTER_STATE = COUNTER_INCRE_HOLD;
        }
        else if ((~PINA & 0x03) == 0x02)
        {
            COUNTER_STATE = COUNTER_DECRE_HOLD, ;
        }
        break;
    case COUNTER_RESET:
        if ((~PINA & 0x03) == 0x03)
        {
            COUNTER_STATE = COUNTER_RESET;
        }
        else
        {
            COUNTER_STATE = COUNTER_INIT;
        }
        break;
    case COUNTER_INCRE:

        if ((~PINA & 0x03) == 0x01)
        {
            COUNTER_STATE = COUNTER_INCRE;
        }
        else
        {
            COUNTER_STATE = COUNTER_INIT;
        }
        break;
    case COUNTER_INCRE_HOLD:
        if (temp >= 10)
        {
            temp = 0x00;
        }
        COUNTER_STATE = COUNTER_INCRE_WAIT;
        break;
    case COUNTER_DECRE_HOLD, :
        if (temp >= 10)
        {
            temp = 0x00;
        }
        COUNTER_STATE = COUNTER_DECRE_WAIT;
        break;
    case COUNTER_INCRE_WAIT:
        if ((~PINA & 0x03) == 0x01)
        {
            ++temp;
            COUNTER_STATE = COUNTER_INCRE_WAIT;
            if (temp >= 10)
            {
                COUNTER_STATE = COUNTER_INCRE_HOLD;
            }
        }
        else
        {
            COUNTER_STATE = COUNTER_INCRE;
        }
        break;

    case COUNTER_DECRE:
        if ((~PINA & 0x03) == 0x02)
        {
            COUNTER_STATE = COUNTER_DECRE;
        }
        else
        {
            COUNTER_STATE = COUNTER_INIT;
        }
        break;
    case COUNTER_DECRE_WAIT:
        if ((~PINA & 0x03) == 0x02)
        {
            COUNTER_STATE = COUNTER_DECRE_WAIT;
            temp++;
            if (temp >= 10)
            {
                COUNTER_STATE = COUNTER_DECRE_HOLD, ;
            }
        }
        else
        {
            COUNTER_STATE = COUNTER_DECRE;
        }
        break;

    default:
        COUNTER_STATE = COUNTER_START;
        break;
    }
    switch (COUNTER_STATE)
    {
    case COUNTER_START:
        PORTB = 0x07;
        break;
    case COUNTER_BEGIN:
        PORTB = 0x07;
        break;
    case COUNTER_INIT:
        temp = 0x00;
        break;
    case COUNTER_INCRE_WAIT:
        break;
    case COUNTER_DECRE_WAIT:
        break;
    case COUNTER_INCRE:
        break;
    case COUNTER_DECRE:
        break;
    case COUNTER_INCRE_HOLD:
        if (PORTB < 9)
        {
            PORTB = PORTB + 1;
        }
        break;
    case COUNTER_DECRE_HOLD, :
        if (PORTB > 0)
        {
            PORTB = PORTB - 1;
        }
        break;
    case COUNTER_RESET:
        PORTB = 0x00;
        break;
    default:
        PORTB = 0x07;
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
    while (1)
    {
        COUNT_SM();
        while (!TimerFlag)
        {
        };
        TimerFlag = 0;
    }
}
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum COUNTER_STATES
{
    COUNTER_INIT,
    COUNTER_INCRE,
    COUNTER_RESET,
    COUNTER_DECRE
} COUNTER_STATES;

void COUNTER_SM()
{

    switch (COUNTER_STATES)
    {
    case COUNTER_INIT:
        if ((~PINA & 0x03) == 0x03)
        {
            PORTC = 0;
            COUNTER_STATES = COUNTER_RESET;
        }
        else if ((~PINA & 0x01) == 0x01 && PORTC < 9)
        {
            PORTC++;
            COUNTER_STATES = COUNTER_INCRE;
        }
        else if ((~PINA & 0x02) == 0x02 && PORTC > 0)
        {
            PORTC--;
            COUNTER_STATES = COUNTER_DECRE;
        }
        else
        {
            COUNTER_STATES = COUNTER_INIT;
        }
        break;

    case COUNTER_INCRE:
        if ((~PINA & 0x03) == 0x03)
        {
            PORTC = 0;
            COUNTER_STATES = COUNTER_RESET;
        }
        else if ((~PINA & 0x01) == 0x01)
        {
            COUNTER_STATES = COUNTER_INCRE;
        }
        else if ((~PINA & 0x00) == 0)
        {
            COUNTER_STATES = COUNTER_INIT;
        }

        break;

    case COUNTER_DECRE:
        if ((~PINA & 0x03) == 0x03)
        {
            PORTC = 0;
            COUNTER_STATES = COUNTER_RESET;
        }
        else if ((~PINA & 0x02) == 0x02)
        {
            COUNTER_STATES = COUNTER_DECRE;
        }
        else if ((~PINA & 0x00) == 0)
        {
            COUNTER_STATES = COUNTER_INIT;
        }

        break;

    case COUNTER_RESET:
        if ((~PINA & 0x03) == 0x03)
        {
            COUNTER_STATES = COUNTER_RESET;
        }
        else if ((~PINA & 0x01) == 0x01)
        {
            PORTC++;
            COUNTER_STATES = COUNTER_INCRE;
        }
        else if ((~PINA & 0x02) == 0x02)
        {
            COUNTER_STATES = COUNTER_INIT;
        }
        break;
    }
}

int main(void)
{

    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;

    COUNTER_STATES = COUNTER_INIT;
    PORTC = 0x07;
    while (1)
    {
        COUNTER_SM();
    }

    return 1;
}
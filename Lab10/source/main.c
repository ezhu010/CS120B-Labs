
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char GetBit(unsigned char x, unsigned char k)
{
    return ((x & (0x01 << k)) != 0);
}

unsigned char GetKeypadKey()
{
    PORTC = 0xEF;
    asm("nop");
    if (GetBit(PINC, 0) == 0)
    {
        return ('1');
    }
    if (GetBit(PINC, 1) == 0)
    {
        return ('4');
    }
    if (GetBit(PINC, 2) == 0)
    {
        return ('7');
    }
    if (GetBit(PINC, 3) == 0)
    {
        return ('*');
    }

    PORTC = 0xDF;
    asm("nop");
    if (GetBit(PINC, 0) == 0)
    {
        return ('2');
    }
    if (GetBit(PINC, 1) == 0)
    {
        return ('5');
    }
    if (GetBit(PINC, 2) == 0)
    {
        return ('8');
    }
    if (GetBit(PINC, 3) == 0)
    {
        return ('0');
    }

    PORTC = 0xBF;
    asm("nop");
    if (GetBit(PINC, 0) == 0)
    {
        return ('3');
    }
    if (GetBit(PINC, 1) == 0)
    {
        return ('6');
    }
    if (GetBit(PINC, 2) == 0)
    {
        return ('9');
    }
    if (GetBit(PINC, 3) == 0)
    {
        return ('#');
    }
    PORTC = 0x7F;
    if (GetBit(PINC, 0) == 0)
    {
        return ('A');
    }

    return ('\0');
}

int main(void)
{
    unsigned char x;
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRC = 0xF0;
    PORTC = 0x0F;
    while (1)
    {
        x = GetKeypadKey();
        switch (x)
        {
        case '\0':
            PORTB = 0x1F;
            break;
        case '1':
            PORTB = 0x01;
            break;
        case '2':
            PORTB = 0x02;
            break;
        case '3':
            PORTB = 0x03;
            break;
        case '4':
            PORTB = 0x04;
            break;
        case '7':
            PORTB = 0x07;
            break;
        case '5':
            PORTB = 0x05;
            break;
        case '6':
            PORTB = 0x06;
            break;
        case '8':
            PORTB = 0x08;
            break;
        case '9':
            PORTB = 0x09;
            break;
        case 'A':
            PORTB = 0x0A;
            break;
        case 'D':
            PORTB = 0x0D;
            break;
        case '*':
            PORTB = 0x0E;
            break;
        case '0':
            PORTB = 0x00;
            break;
        case '#':
            PORTB = 0x0F;
            break;
        default:
            PORTB = 0x1B;
            break;
        }
    }
}

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

    PORTC = 0xBF;
    asm("nop");
    return ('\0')
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
        case '/0':
            PORTB = 0x1F;
            break;
        case '1':
            PORTB = 0x01;
            break;
        case '2':
            PORTB = 0x02;
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

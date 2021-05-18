#include <avr/io.h>
#include <timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef struct task
{
    signed char state;
    unsigned long period;
    unsigned long elapsedTime; //Time elapsed since last task tick
    int (*TickFct)(int);       //Task tick function
} task;

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
    if (GetBit(PINC, 1) == 0)
    {
        return ('B');
    }
    if (GetBit(PINC, 2) == 0)
    {
        return ('C');
    }
    if (GetBit(PINC, 3) == 0)
    {
        return ('D');
    }
    return ('\0');
}

unsigned char x = 0x00;
unsigned char keypad = 0x00;

enum KEYPADSTATES
{
    KEYPAD_INIT
};
int KEYPAD_SM(int state)
{
    x = GetKeypadKey();
    switch (state)
    {
    case KEYPAD_INIT:
        state = KEYPAD_INIT;
        break;
    }
    switch (state)
    {
    case KEYPAD_INIT:
        switch (x)
        {
        case '\0':
            keypad = 0x00;
            break;
        case '1':
            keypad = 0x80;
            break;
        case '2':
            keypad = 0x80;
            break;
        case '3':
            keypad = 0x80;
            break;
        case '4':
            keypad = 0x80;
            break;
        case '5':
            keypad = 0x80;
            break;
        case '6':
            keypad = 0x80;
            break;
        case '7':
            keypad = 0x80;
            break;
        case '8':
            keypad = 0x80;
            break;
        case '9':
            keypad = 0x80;
            break;
        case 'A':
            keypad = 0x80;
            break;
        case 'B':
            keypad = 0x80;
            break;
        case 'C':
            keypad = 0x80;
            break;
        case 'D':
            keypad = 0x80;
            break;
        case '*':
            keypad = 0x80;
            break;
        case '0':
            keypad = 0x80;
            break;
        case '#':
            keypad = 0x80;
            break;
        default:
            keypad = 0x00;
            break;
        }
        PORTB = keypad;
        break;
    }
    return state;
}

int main(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRC = 0xF0;
    PORTC = 0x0F;
    /* Insert your solution below */
    static task task1;
    task *tasks[] = {&task1};
    const unsigned short numTasks = sizeof(tasks) / sizeof(task *);
    const char start = 0;
    task1.state = start;
    task1.period = 50;
    task1.elapsedTime = task1.period;
    task1.TickFct = &KEYPAD_SM;

    TimerSet(50);
    TimerOn();

    unsigned short i;
    while (1)
    {
        for (i = 0; i < numTasks; ++i)
        {
            if (tasks[i]->elapsedTime == tasks[i]->period)
            {
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += 50;
        }
        while (!TimerFlag)
            ;
        TimerFlag = 0;
    }
    return 1;
}

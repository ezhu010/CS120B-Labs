
#include <avr/io.h>
#include "timer.h"
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

enum Demo_States
{
    shift
};
int Demo_Tick(int state)
{

    // Local Variables
    static unsigned char pattern = 0x80; // LED pattern - 0: LED off; 1: LED on
    static unsigned char row = 0xFE;     // Row(s) displaying pattern.
                                         // 0: display pattern on row
                                         // 1: do NOT display pattern on row

    static unsigned char column = 0x00;
    // Transitions
    switch (state)
    {
    case shift:
        break;
    default:
        state = shift;
        break;
    }
    // Actions
    switch (state)
    {
    case shift:
        if (row == 0xEF && pattern == 0x01)
        { // Reset demo
            pattern = 0x80;
            row = 0xFE;
        }
        else if (pattern == 0x01)
        { // Move LED to start of next row
            pattern = 0x80;
            row = (row << 1) | 0x01;
        }
        else
        { // Shift LED one spot to the right on current row
            pattern >>= 1;
        }
        break;
    default:
        break;
    }
    PORTC = pattern; // Pattern to display
    PORTD = column;
}

int main(void)
{
    DDRD = 0xFF;
    PORTD = 0x00;
    DDRC = 0xFF;
    PORTC = 0x00;
    static task task1;
    task *tasks[] = {&task1};
    const unsigned short numTasks = sizeof(tasks) / sizeof(task *);
    const char start = 0;
    task1.state = start;
    task1.period = 100;
    task1.elapsedTime = task1.period;
    task1.TickFct = &Demo_Tick;

    TimerSet(100);
    TimerOn();
    unsigned short i;
    while (1)
    {
        PORTD = 0xFE;
        PORTC = 0x80;
        //     for (i = 0; i < numTasks; ++i)
        //     {
        //         if (tasks[i]->elapsedTime == tasks[i]->period)
        //         {
        //             tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
        //             tasks[i]->elapsedTime = 0;
        //         }
        //         tasks[i]->elapsedTime += 100;
        //     }
        //     while (!TimerFlag)
        //     {
        //     };
        //     TimerFlag = 0;
        // }
    }
}
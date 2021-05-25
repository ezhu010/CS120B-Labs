
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
    static unsigned char column = 0x1E;
    // static unsigned char row = 0x80;
    static unsigned char row = 0x34;

    // Transitions
    switch (state)
    {
    case shift:
        if (column == 0xEF) //&& row == 0x01
        {
            column = 0x1E;
            //row = 0x80;
        }
        // else if (column == 0xEF)
        // {
        //     column = 0x1E;
        //     row = row >> 1;
        // }
        else
        {
            column = (column << 1) + 1;
        }
        break;
    default:
        state = shift;
        break;
    }
    // Actions
    // switch (state)
    // {
    // case shift:
    //     column <<= 1;
    //     break;
    // default:
    //     break;
    // }
    PORTC = row; // Pattern to display
    PORTD = column;
    return state;
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
    task1.period = 200;
    task1.elapsedTime = task1.period;
    task1.TickFct = &Demo_Tick;

    TimerSet(200);
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
            tasks[i]->elapsedTime += 200;
        }
        while (!TimerFlag)
        {
        };
        TimerFlag = 0;
    }
}

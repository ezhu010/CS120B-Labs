#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

enum Random_States
{
    random_init
};
int temp = 0;
int random_tick(int state)
{
    switch (state)
    {
    case random_init:
        temp = rand() % 255 + 1;
        break;
    }
    return state;
}

enum Demo_States
{
    shift
};
int LED_MATRIX(int state)
{
    static unsigned char column = 0x1E;
    unsigned char row = 0x80;
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

    PORTC = row; // Pattern to display
    PORTD = column;
    return state;
}

int main(void)
{
    srand(time(0));
    DDRD = 0xFF;
    PORTD = 0x00;
    DDRC = 0xFF;
    PORTC = 0x00;
    static task task1;
    task *tasks[] = {&task1};
    const unsigned short numTasks = sizeof(tasks) / sizeof(task *);
    const char start = 0;
    task1.state = start;
    task1.period = 300;
    task1.elapsedTime = task1.period;
    task1.TickFct = &LED_MATRIX;

    // task2.state = start;
    // task2.period = 1800;
    // task2.elapsedTime = task2.period;
    // task2.TickFct = &random_tick;

    TimerSet(300);
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
            tasks[i]->elapsedTime += 300;
        }
        while (!TimerFlag)
        {
        };
        TimerFlag = 0;
    }
}

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

enum LED_Matrix_States
{
    init,
    shift
};
int LED_MATRIX(int state)
{
    static unsigned char column = 0x0E;
    unsigned char row = temp;
    switch (state)
    {
    case init:
        row = temp;
        column = 0x0E;
        state = shift;
        break;
    case shift:
        if (column == 0xEF)
        {
            column = 0x0E;
        }
        else
        {
            column = ((column << 1) & 0x0E) + 1;
        }
        break;
    }
    PORTC = row;
    PORTD = column;
    return state;
}

enum PLAYER_STATES
{
    PLAYER_INIT
};

int PLAYER_SM(int state)
{
    switch (state)
    {
    case PLAYER_INIT:
        PORTC = 0x10;
        PORTD = 0x0F;
        break;
    }
    return state;
}

int main(void)
{
    srand(time(0));
    DDRD = 0xFF;
    PORTD = 0x00;
    DDRC = 0xFF;
    PORTC = 0x00;
    static task task1, task2, task3;
    task *tasks[] = {&task1, &task2, &task3};
    // task *tasks[] = {&task3};

    const unsigned short numTasks = sizeof(tasks) / sizeof(task *);
    const char start = 0;
    task1.state = start;
    task1.period = 2500;
    task1.elapsedTime = task1.period;
    task1.TickFct = &random_tick;

    task2.state = start;
    task2.period = 500;
    task2.elapsedTime = task2.period;
    task2.TickFct = &LED_MATRIX;

    task3.state = start;
    task3.period = 50;
    task3.elapsedTime = task3.period;
    task3.TickFct = &PLAYER_SM;
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
            tasks[i]->elapsedTime += 100;
        }
        while (!TimerFlag)
        {
        };
        TimerFlag = 0;
    }
}

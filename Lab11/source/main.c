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
int random_counter = 599;
int temp = 0;
int newTimer = 600;

// This function gets the random variable to display for the row.

int random_tick(int state)
{
    random_counter++;
    if (random_counter == newTimer)
    {
        switch (state)
        {
        case random_init:
            temp = rand() % 255 + 1;
            break;
        }
        random_counter = 0;
    }
    return state;
}

enum LED_Matrix_States
{
    init,
    shift
};
unsigned char column = 0x1E;
unsigned char row;
int count = 0;
int led_ticker = 120;
int LED_MATRIX(int state)
{
    count++;
    switch (state)
    {
    case init:
        row = temp;
        column = 0x1E;
        state = shift;
        break;
    case shift:
        row = temp;
        if (column == 0xEF && count == led_ticker)
        {
            column = 0x1E;
            count = 0;
        }
        else if (count == led_ticker)
        {
            column = ((column << 1) + 1);
            count = 0;
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
int counter2 = 0;
int player = 0x10;
int PLAYER_SM(int state)
{
    counter2++;
    switch (state)
    {
    case PLAYER_INIT:
        if (counter2 == 5)
        {
            PORTC = player;
            PORTD = 0x0F;
            counter2 = 0;
        }
        else if ((player & temp) > 0 && column == 0xEF)
        {
            PORTB = 1;
        }
        else if (column != 0xEF)
        {
            PORTB = 0;
        }

        else
        {
            PORTC = row;
            PORTD = column;
        }

        break;
    }
    return state;
}

enum PLAYER_MOVE
{
    BUTTON_INIT,
    BUTTON_PRESS,
};
int count3 = 0;
int PLAYER_MOVE_SM(int state)
{
    count3++;
    if (count3 == 50)
    {
        switch (state)
        {
        case BUTTON_INIT:
            if ((~PINA & 0x01) == 0x01 && player != 0x80)
            {
                player = player << 1;
                state = BUTTON_PRESS;
            }
            else if ((~PINA & 0x02) == 0x02 && player != 0x01)
            {
                player = player >> 1;
                state = BUTTON_PRESS;
            }
            else
            {
                state = BUTTON_INIT;
            }
            break;
        case BUTTON_PRESS:
            if ((~PINA & 0x01) == 0x01)
            {
                state = BUTTON_PRESS;
            }
            else if ((~PINA & 0x02) == 0x02)
            {
                state = BUTTON_PRESS;
            }
            else
            {
                state = BUTTON_INIT;
            }
        }
        count3 = 0;
    }
    return state;
}

static task task1, task2, task3, task4;
task *tasks[] = {&task1, &task2, &task3, &task4};

int main(void)
{
    srand(time(0));
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRD = 0xFF;
    PORTD = 0x00;
    DDRC = 0xFF;
    PORTC = 0x00;
    int totalTimeElapsed = 0;

    const unsigned short numTasks = sizeof(tasks) / sizeof(task *);
    const char start = 0;
    task1.state = start;
    task1.period = 10;
    task1.elapsedTime = task1.period;
    task1.TickFct = &random_tick;

    task2.state = start;
    task2.period = 10;
    task2.elapsedTime = task2.period;
    task2.TickFct = &LED_MATRIX;

    task3.state = start;
    task3.period = 1;
    task3.elapsedTime = task3.period;
    task3.TickFct = &PLAYER_SM;

    task4.state = start;
    task4.period = 1;
    task4.elapsedTime = task4.period;
    task4.TickFct = &PLAYER_MOVE_SM;
    TimerSet(1);
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
            tasks[i]->elapsedTime += 1;
        }
        // if (totalTimeElapsed == 6000)
        // {
        //     task2.period = 3;
        //     newTimer = 180;
        // }
        totalTimeElapsed += 1;

        while (!TimerFlag)
        {
        };
        TimerFlag = 0;
    }
}

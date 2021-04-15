


#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int count = 0;
int arr[4];

enum DOOR_STATES
{
    DOOR_START,
    BUTTON_PRESSED,
    DOOR_WAIT,
    DOOR_UNLOCK,
    DOOR_LOCK,
} DOOR_STATE;

void DOOR_SM()
{
    switch (DOOR_STATE)
    {
    case DOOR_START:
        if (PINA == 0x00)
        {
            DOOR_STATE = DOOR_LOCK;
        }
        else
        {
            arr[count] = PINA;
            count++;
            DOOR_STATE = BUTTON_PRESSED;
        }
        break;

    case BUTTON_PRESSED:
        if (PINA != 0)
        {
            DOOR_STATE = BUTTON_PRESSED;
        }
        else if (PINA == 0)
        {
            DOOR_STATE = DOOR_WAIT;
        }

        break;

    case DOOR_WAIT:
        if (PINA == 0)
        {
            DOOR_STATE = DOOR_WAIT;
        }
        else
        {
            arr[count] = PINA;
            count++;
            if (count == 4)
            {
                if (arr[0] == 0x04 && arr[1] == 0x01 && arr[2] == 0x02 && arr[3] == 0x01)
                {
                    DOOR_STATE = DOOR_UNLOCK;
                }
                else
                {
                    DOOR_STATE = DOOR_LOCK;
                }
            }
            else
            {
                DOOR_STATE = BUTTON_PRESSED;
            }
        }
        break;

    case DOOR_UNLOCK:
        break;

    case DOOR_LOCK:
        if (PINA == 0x80)
        {
            DOOR_STATE = DOOR_LOCK;
        }
        else if (PINA == 0)
        {
            DOOR_STATE = DOOR_LOCK;
        }
        break;
    }

    switch (DOOR_STATE)
    {
    case DOOR_START:
        break;
    case DOOR_LOCK:
        PORTB = 0x00;
        break;
    case BUTTON_PRESSED:
        break;
    case DOOR_UNLOCK:
        PORTB = 0x01;
        break;
    case DOOR_WAIT:
        break;
    }
}

int main(void)
{
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0x0FF;
    PORTB = 0x00;
    DOOR_STATE = DOOR_START;

    while (1)
    {
        DOOR_SM();
    }
    return 1;
}


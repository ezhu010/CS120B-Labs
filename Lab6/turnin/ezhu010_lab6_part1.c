/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum LIGHT_STATES {LIGHT_INIT, LIGHT_ONE,LIGHT_TWO, LIGHT_THREE} LIGHT_STATE;

void LIGHT_SM(){
	switch(LIGHT_STATE){
		case LIGHT_INIT:
			LIGHT_STATE = LIGHT_ONE;
			break;
		case LIGHT_ONE:
			LIGHT_STATE = LIGHT_TWO;
			break;
		case LIGHT_TWO:
			LIGHT_STATE = LIGHT_THREE;
			break;
		case LIGHT_THREE:
			LIGHT_STATE = LIGHT_ONE;
			break;
	}
	switch(LIGHT_STATE){
		case LIGHT_INIT:
			break;
		case LIGHT_ONE:
			PORTB = 0x01;
			break;
		case LIGHT_TWO:
			PORTB = 0x02;
			break;
		case LIGHT_THREE:
			PORTB = 0x04;
			break;
		}
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;
	PORTB = 0x00;
	//unsigned char tmpB = 0;
	TimerSet(1000);
	TimerOn();
	LIGHT_STATE = LIGHT_INIT;
    /* Insert your solution below */
    while (1) {
	//tmpB = ~tmpB;
	//PORTB = tmpB;
	LIGHT_SM();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

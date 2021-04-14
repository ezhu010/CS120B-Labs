#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
enum COUNTER_STATE {COUNTER_START, COUNTER_INIT, COUNTER_INCRE, COUNTER_DECRE, COUNTER_RESET, COUNTER_WAIT} COUNTER_STATE;
#endif

void COUNTER_SM() {
	unsigned char A1 = PINA & 0x02;
	unsigned char A0 = PINA & 0x01;  

	switch(COUNTER_STATE){ //Transitions
		case COUNTER_START: 
			COUNTER_STATE = COUNTER_INIT;
			break;

		case COUNTER_INIT: 
			if (A0 && !A1)
				COUNTER_STATE = COUNTER_INCRE;
			else if (A1 && !A0)
				COUNTER_STATE = COUNTER_DECRE;
			else if (A0 && A1)
				COUNTER_STATE = COUNTER_RESET;
			else
				COUNTER_STATE = COUNTER_WAIT;
			break;

		case COUNTER_INCRE: 
			COUNTER_STATE = COUNTER_WAIT;
			break;

		case COUNTER_DECRE: 
			COUNTER_STATE = COUNTER_WAIT;
			break;

		case COUNTER_WAIT:
			if (A0 && A1)
				COUNTER_STATE = COUNTER_RESET;
			else if (!A0 && !A1)
				COUNTER_STATE = COUNTER_INIT;
			else
				COUNTER_STATE = COUNTER_WAIT;
			break;

		case COUNTER_RESET: 
			if (A0 && A1)
				COUNTER_STATE = COUNTER_RESET;
			else
				COUNTER_STATE = COUNTER_WAIT;
			break;

		default: 
			COUNTER_STATE = COUNTER_START;
			break;

	}


	switch(COUNTER_STATE){ 
		case COUNTER_START: 
			PORTC = 0x07;
			break;
		
		case COUNTER_INIT:
			PORTC = 0x07;
			break;		
	
		case COUNTER_INCRE: 
			if (PORTC < 0x09)
				PORTC++;
			else 
				PORTC = 0x09;
			break;
		case COUNTER_DECRE: 
			if (PORTC > 0x00)
				PORTC--;
			else
				PORTC = 0x00;
			break;
		case COUNTER_WAIT:
			break;
		case COUNTER_RESET:
			PORTC = 0x00;
			break;
		default:
			PORTC = 0x07;
		break; 


	}
}


int main(void) {

	DDRA = 0x00; PORTA = 0xFF; 
	DDRC = 0xFF; PORTC = 0x00;
	COUNTER_STATE = COUNTER_START;
	    
	while (1) { 
		COUNTER_SM();

	}

	return 1;
}

/*	Author: ezhu010
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

unsigned char GetBit(unsigned char x, unsigned char k){
        return ((x & (0x01 << k)) != 0);
}

int main(void) {
        DDRA = 0x00; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char temp = 0;
	while(1){
	    temp = PINA;
	    if(temp == 0){
		PORTC = 0x40; 
	    }
	    if(temp == 1 || temp == 2){
		PORTC = 0x60;
	    } 
	    if(temp == 3 || temp == 4){
		PORTC = 0x70;
	    }
	    if(temp == 5 || temp == 6){
		PORTC = 0x38;
	    }
	    if(temp >= 7 && temp <= 9){
		PORTC = 0x3C;
	    }
	    if(temp >= 10 && temp <= 12){
		PORTC = 0x3E;
	    }
	    if(temp >= 13 && temp <= 15){
		PORTC = 0x3F;
	    } 

	}
        return 0;
}



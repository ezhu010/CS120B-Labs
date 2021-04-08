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
	
	DDRB = 0x01; PORTB = 0x00;
	DDRD = 0x00; PORTD = 0xFF;
	unsigned char temp = 0;
	unsigned char temp2 = 0;
	unsigned char total = 0;
	while(1){
		temp = PIND;
		temp2 = PINB;
		total = (temp << 1) | (temp2 & 0x01);
	        if(total >= 0x46){
		   PORTB = 0x02;
	        }
	        else if(total > 5 && total <= 70){
		   PORTB = 0x04;
	       }
		else{
		   PORTB = 0x00;
		}	
	}

        return 0;
}



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

int main(void) {
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0x00; PORTB = 0x00;
	DDRC = 0x00; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	unsigned char weight1 = 0;
	unsigned char weight2 = 0;
	unsigned char weight3 = 0;
	unsigned char total = 0; 

	while(1){
		weight1 = PINA;
		weight2 = PINB;
		weight3 = PINC;
	        total = weight1 + weight2 + weight3;
		if(total > 140){
		    PORTD = PORTD + 1;
   		}
		if((weight1 - weight3) > 80 || (weight3 - weight1) > 80){
		   PORTD = PORTD | 0x02;
		} 
		PORTD = total << 2; 			
	}

	return 0;
}

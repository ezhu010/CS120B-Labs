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

        DDRA = 0x00;
        DDRC = 0xFF;
        PORTA = 0xFF;
        PORTC = 0x00;

        unsigned char cntavail  = 0;
        while(1){
	/*
	 temp = PINA;
	 if(temp == 0x0F){
		PORTC = 0x80;
	   }
	 else{
	        PORTC = !(PINA & 0x01)*1 + !(PINA & 0x02) * 2 + !(PINA & 0x04) * 4 + !(PINA & 0x08) * 8;
	    } 
	*/
           cntavail =!(PINA & 0x01) + !(PINA & 0x02) + !(PINA & 0x04) + !(PINA & 0x08);
	   if(cntavail == 0){
		PORTC = 0x80;
	   }
           else{
           PORTC = cntavail;
	  }
        }
        return 0;
}

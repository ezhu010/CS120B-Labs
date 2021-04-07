/*	Author: Edward Zhu
 *  Partner(s) Name: 
 *	Lab Section: 023
 *	Assignment: Lab #2  Exercise #1
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
	DDRB = 0x0F;
	unsigned char temp = 0;
 
	while(1){
		
	   temp = PINA;
	   if(temp == 0){
		PORTB = 0x00;
	   }
	   else if(temp == 1){
		PORTB = 0x01;
	  }
	  else if(temp == 2){
		PORTB = 0x00;
	  }
	  else if(temp == 3){
		PORTB = 0x00;
	  }

	}
	
	return 0;


}

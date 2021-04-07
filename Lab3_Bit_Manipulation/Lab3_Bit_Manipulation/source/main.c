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
        DDRB = 0x00; PORTB = 0x00;
        DDRC = 0xFF; PORTC = 0x00;
        unsigned char num1 = 0;
        unsigned char num2 = 0;
        unsigned char temp = 0;
        unsigned char i = 0;
        unsigned char j = 0;
        while(1){
            num1 = PINA;
            num2 = PINB;
            temp = 0;
            for(i = 0; i < 8; i++){
                if(GetBit(num1,i)){
                    temp++;
                }
            }
            for(j = 0; j < 8; j++){
                if(GetBit(num2, j)){
                    temp++;
                }
            }
            PORTC = temp;
        }

        return 0;
}



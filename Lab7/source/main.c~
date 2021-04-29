

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned short x = 0x00;
unsigned short max = 200;

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1<< ADATE);
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    ADC_init();
    while (1) {
	x = ~ADC;
	unsigned char temp = x;
	if (temp >= max/2) {
		PORTB = 0x01;
	}
	else {
		PORTB = 0x00;
	}
    }
    return 0;
}

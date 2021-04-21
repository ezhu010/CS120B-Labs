





#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LIGHT_STATES {WAIT, LIGHT_ONE, WAIT_ONE, LIGHT_THREE, WAIT_THREE, LIGHT_FIVE, WAIT_FIVE, LIGHT_TWO, WAIT_TWO,LIGHT_FOUR, WAIT_FOUR,LIGHT_SIX, WAIT_SIX,  RESET}   LIGHT_STATE;

void LIGHT_SM(){
	switch(LIGHT_STATE){
	   case WAIT:
		   if(~PINA & 0x01){
		    
			   LIGHT_STATE = LIGHT_ONE;
		  }
		  else{
			  LIGHT_STATE = WAIT;
		 }

		   break;	
	case LIGHT_ONE:
		   if(~PINA & 0x01){
			   LIGHT_STATE = LIGHT_ONE;
		}
		   else{
			   LIGHT_STATE = WAIT_ONE;
			 }
		break;
	case WAIT_ONE:
		if(~PINA & 0x01){
			LIGHT_STATE = LIGHT_THREE;
		}
		else{
			LIGHT_STATE = WAIT_ONE;
		}
		break;
	case LIGHT_THREE:
		if(~PINA & 0x01){
			LIGHT_STATE = LIGHT_THREE;
		}
		else{
			LIGHT_STATE = WAIT_THREE;
		}
		break;
	case WAIT_THREE:
		if(~PINA & 0x01){
			LIGHT_STATE = LIGHT_FIVE;
		}
		else{
			LIGHT_STATE = WAIT_THREE;
		}
		break;

	 
	case LIGHT_FIVE:
                if(~PINA & 0x01){
                        LIGHT_STATE = LIGHT_FIVE;
                }
                else{
                        LIGHT_STATE = WAIT_FIVE;
                }
                break;
	
	case WAIT_FIVE:
                if(~PINA & 0x01){
                        LIGHT_STATE = LIGHT_TWO;
                }
                else{
                        LIGHT_STATE = WAIT_FIVE;
                }
                break;
	case LIGHT_TWO:
                if(~PINA & 0x01){
                        LIGHT_STATE = LIGHT_TWO;
                }
                else{
                        LIGHT_STATE = WAIT_TWO;
                }
                break;

	case WAIT_TWO:
                if(~PINA & 0x01){
                        LIGHT_STATE = LIGHT_FOUR;
                }
                else{
                        LIGHT_STATE = WAIT_TWO;
                }
                break;
	case LIGHT_FOUR:
                if(~PINA & 0x01){
                        LIGHT_STATE = LIGHT_FOUR;
                }
                else{
                        LIGHT_STATE = WAIT_FOUR;
                }
                break;
	case WAIT_FOUR:
                if(~PINA & 0x01){
                        LIGHT_STATE = LIGHT_SIX;
                }
                else{
                        LIGHT_STATE = WAIT_FOUR;
                }
                break;
	case LIGHT_SIX:
                if(~PINA & 0x01){ 
                        LIGHT_STATE = LIGHT_SIX;
                }
                else{
                        LIGHT_STATE = WAIT_SIX;
                }
                break;

	case WAIT_SIX:
                if(~PINA & 0x01){ 
                        LIGHT_STATE = RESET;
                }
                else{
                        LIGHT_STATE = WAIT_SIX;
                }
                break;






	case RESET:
		if(~PINA & 0x01){
			LIGHT_STATE = RESET;
		}
		else{
			LIGHT_STATE = WAIT;
		}
		break;

	}

	switch(LIGHT_STATE){
		case WAIT:
			PORTB = 0x00;
			break;
		case LIGHT_ONE:
			PORTB = 0x01;
			break;
		case WAIT_ONE:
			PORTB = 0x01;
			break;
		case LIGHT_THREE:
			PORTB = 0x04;
			break;
		case WAIT_THREE:
			PORTB = 0x04;
			break;
		case LIGHT_FIVE:
                        PORTB = 0x10;
                        break;
		case WAIT_FIVE:
                        PORTB = 0x10;
                        break;
		case LIGHT_TWO:
                        PORTB = 0x02;
                        break;
		case WAIT_TWO:
			PORTB = 0x02;
			break;
		case LIGHT_FOUR:
                        PORTB = 0x08;
                        break;
		case WAIT_FOUR:
			PORTB = 0x08;
			break;
		case LIGHT_SIX:
                        PORTB = 0x20;
                        break;
		case WAIT_SIX:
                        PORTB = 0x20;
                        break;

		case RESET:
			PORTB = 0x00;
			break;
	

	}

}


int main(void) {
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	LIGHT_STATE = WAIT;
	while(1){
	  //if(~PINA & 0x01){
	//	  PORTB = 0xFF;

	  // }
	  //else{
	//	  PORTB = 0x00;
//	}
	  LIGHT_SM();
	}

	return 1;
}



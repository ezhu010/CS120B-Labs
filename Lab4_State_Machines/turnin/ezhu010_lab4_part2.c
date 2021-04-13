/*	Author: Edward Zhu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum COUNTER_STATE { COUNTER_BEGIN, COUNTER_INIT, COUNTER_RESET, COUNTER_INCRE, COUNTER_DECRE, COUNTER_WAIT} COUNTER_STATE; 


void COUNTER_SM_TICK(){
	
	switch(COUNTER_STATE){
		case COUNTER_BEGIN:
		     COUNTER_STATE = COUNTER_INIT;
	   	     break;
	
		case COUNTER_INIT:
	 	     if(PINA == 0x01){
			    COUNTER_STATE = COUNTER_INCRE;
		      }
		     else if( PINA == 0x02){
			    COUNTER_STATE = COUNTER_DECRE;
		     }
		    else if( PINA == 0x03){
			    COUNTER_STATE = COUNTER_RESET;
		    }
		    else {
			COUNTER_STATE = COUNTER_WAIT; 
		    }
		    break;

	      case COUNTER_INCRE:
		    COUNTER_STATE = COUNTER_WAIT;
		    break;

	     case COUNTER_DECRE:
		   COUNTER_STATE = COUNTER_WAIT;
		   break;

	     case COUNTER_WAIT:
		   if(PINA == 0x03){
		      COUNTER_STATE = COUNTER_RESET;
		   }
		   else if(PINA == 0x00){
			COUNTER_STATE = COUNTER_INIT;
		   }
		   else {
			COUNTER_STATE = COUNTER_WAIT;
		   }
	            break;


	    case COUNTER_RESET:
		   if(PINA == 0x03){
			COUNTER_STATE = COUNTER_RESET;
		   }

		   else{
			COUNTER_STATE = COUNTER_WAIT;
		   }

		  break;
	}

	switch(COUNTER_STATE){

		case COUNTER_BEGIN:
		      PORTC = 0x07;
		      break;	
	

	       case COUNTER_INIT:
		     PORTC = 0x07;
		     break;

	       case COUNTER_INCRE:
		     if(PORTC < 0x09){
			    PORTC = PORTC = 1;
		     }
		     else{
			    PORTC = 0x09;
		     }
		    break;
	
	      case COUNTER_DECRE:
		     if(PORTC > 0x00){
		          PORTC = PORTC - 1;
			}
		      else{
			 PORTC = 0x00;
		     }

		    break;



	     case COUNTER_WAIT:
		    break;

	    case COUNTER_RESET:
		    PORTC = 0x00;
		    break;

	}


}




int main(void) {

	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	COUNTER_STATE = COUNTER_BEGIN; 	

	while(1){

           COUNTER_SM_TICK();

	}	


	return 1;
}

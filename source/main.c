/*	Author: dsale010
 *  Partner(s) Name: 
 *	Lab Section:22
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define inc_button (PINA & 0x01)
#define dec_button (PINA & 0x02)

enum States {START, WAIT, A0_PRESS, A0_RELEASE, A1_PRESS, A1_RELEASE, RESET, ADD, SUB} state;
unsigned char outtie = 7;

void tick(){
    switch(state){  //Transitions
        case START:
        case WAIT:
            if ((inc_button == 0x01) && (dec_button == 0x02))
                state = RESET;
            
            else if (!(inc_button == 0x01) && (dec_button == 0x02))
                state = A1_PRESS;
            
            else if ((inc_button == 0x01) && !(dec_button == 0x02))
                state = A0_PRESS;
            
            else if (!(inc_button == 0x01) && !(dec_button == 0x02))
                state = WAIT;
            break;
            
        case A0_PRESS:
            if ((inc_button == 0x01) && (dec_button == 0x02))
                state = RESET;
            
            else if (!(inc_button == 0x01) && (dec_button == 0x02))
                state = A0_RELEASE;
            
            else if ((inc_button == 0x01) && !(dec_button == 0x02))
                state = A0_PRESS;
            
            else if (!(inc_button == 0x01) && !(dec_button == 0x02))
                state = A0_RELEASE;
            break;
            
        case A0_RELEASE:
           if ((inc_button == 0x01) && (dec_button == 0x02))
                state = RESET;
           else
               state = (outtie < 9) ? ADD : WAIT;
           break;
            
        case ADD:
            state = WAIT;
            break;
            
        case A1_PRESS:
            if ((inc_button == 0x01) && (dec_button == 0x02))
                state = RESET;
            
            else if (!(inc_button == 0x01) && (dec_button == 0x02))
                state = A1_PRESS;
            
            else if ((inc_button == 0x01) && !(dec_button == 0x02))
                state = A1_RELEASE;
            
            else if (!(inc_button == 0x01) && !(dec_button == 0x02))
                state = A1_RELEASE;
            
            break;
            
        case A0_RELEASE:
           if ((inc_button == 0x01) && (dec_button == 0x02))
                state = RESET;
           else
               state = (outtie > 0) ? SUB : WAIT;
            
           break;
            
        case SUB:
            state = WAIT;
            break;
            
        case RESET:
            state = WAIT;
            break;
            
    }
    
    switch(state){  //Actions
        case ADD:
            outtie += 1;
            break;
            
        case SUB:
            outtie -= 1;
            break;
            
        default:
            break;
    }
    
    PORTC = outtie;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;    PORTA = 0xFF;
    DDRC = 0xFF;    PORTC = 0x00;
    
    state = START;

    /* Insert your solution below */
    while (1) {
        tick();
    }
    return 1;
}

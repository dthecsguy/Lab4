/*	Author: dsale010
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

#define button (PINA & 0x01)

enum States {START, OFF_UNPRESSED, OFF_PRESSED, ON_UNPRESSED, ON_PRESSED} state;
unsigned char leds = 0;

void tick(){
    switch(state){  //Transitions
        case START:
        case OFF_UNPRESSED:
            state = (button == 0x01) ? OFF_PRESSED : OFF_UNPRESSED;
            break;
            
        case OFF_PRESSED:
            state = (button == 0x01) ? OFF_PRESSED : ON_UNPRESSED;
            break;
            
        case ON_UNPRESSED:
            state = (button == 0x01) ? ON_PRESSED : ON_UNPRESSED;
            break;
            
        case ON_PRESSED:
            state = (button == 0x01) ? ON_PRESSED : OFF_UNPRESSED;
            break;
    }
    
    switch(state){  //Actions
            case OFF_UNPRESSED:
            leds = 0x01;
            break;
            
        case OFF_PRESSED:
            leds = 0x02;
            break;
            
        case ON_UNPRESSED:
            leds = 0x02;
            break;
            
        case ON_PRESSED:
            leds = 0x01;
            break;
    }
    
    PORTB = leds;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;    PORTA = 0xFF;
    DDRB = 0xFF;    PORTB = 0x00;
    
    state = START;

    /* Insert your solution below */
    while (1) {
        tick();
    }
    return 1;
}

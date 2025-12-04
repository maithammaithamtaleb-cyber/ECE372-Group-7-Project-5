// Description: This file implements the initialization of an external interrupt
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PD0 and sets it into input mode
 */
void initSwitchPD0(){
    DDRD &= ~(1<<DDD2); // I/P
    PORTD |= (1<<PORTD2); //Pull Up Resistor

    EICRA &= ~(1<<ISC21);
    EICRA |= (1<<ISC20);

    EIFR = (1<<INTF2);
    EIMSK |= (1<<INT2);
}

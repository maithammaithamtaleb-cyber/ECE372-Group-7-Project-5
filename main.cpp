/*
Group 7: Maitham Taleb, Jack Tripp, Jack Nettle, Joseph McLaughlin, Chris Hampton.
Date: 11/01/2025
Course: Microprocessor organization
Description: Main program file for changing speed and direction of a DC motor using
a switch and potentiometer.
*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer1.h"
#include "switch.h"
#include "pwm.h"



typedef enum button_states {
  wait_press, debounce_press, wait_release, debounce_release
} stateType;
stateType state = wait_press;

//volatile int count;
volatile int delay_ms;
//volatile state debounce_state = wait_press;



int main() {
    sei(); // Enable global interrupts
    //initial
    int smile[] =   {0b00111100,
                     0b01000010,
                     0b10100101,
                     0b10000001,
                     0b10100101,
                     0b10011001,
                     0b01000010,
                     0b00111100};

    int frown[] =   {0b00111100,
                     0b01000010,
                     0b10100101,
                     0b10000001,
                     0b10011001,
                     0b10100101,
                     0b01000010,
                     0b00111100};
    
    float buzz = 0;

    while(1){
        
        switch(state) {
            case wait_press:
            changeDutyCycle(buzz); 

                break;
            case debounce_press:
                ms_delay(1);//Timer 0
                state = wait_release;

                break;
            case wait_release:
                
                break;
            case debounce_release:
                changeDutyCycle(2.5); //turns off motor -chris
                ms_delay(1);
            state = wait_press;

            break;
    }
   
    }
    return 0; 
}
ISR(INT0_vect){
    if(state == wait_press){
        state = debounce_press; // Transition to debounce_press state
    }
    else if(state == wait_release){
        state = debounce_release; // Transition to debounce_release state
    }
}








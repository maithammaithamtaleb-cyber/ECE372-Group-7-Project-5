/*
Group 7: Maitham Taleb, Jack Tripp, Jack Nettle, Joseph McLaughlin, Chris Hampton.
Date: 11/01/2025
Course: Microprocessor organization
Description: Main program file for changing speed and direction of a DC motor using
a switch and potentiometer.
*/

#include "Arduino.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "timer1.h"
#include "switch.h"
#include "pwm.h"
#include "i2c.h"
#include "spi.h"

#define THRESHOLD 16700

typedef enum tilt_states {
    NORMAL, TILTED
} tilt_stateType;
tilt_stateType tiltState = NORMAL;

typedef enum button_states {
  wait_press, debounce_press, wait_release, debounce_release
} stateType;
stateType state = wait_press;

//volatile int count;
volatile int delay_ms;
//volatile state debounce_state = wait_press;



int main() {
    Serial.begin(9600);
    initPWM_Pins();
    SPI_Init();
    initI2C();
    initSwitchPD0();
    timer1_init();
     MAX7219_Init();
    sei(); // Enable global interrupts
    //initial
    Serial.print("here");
    changeDutyCycle(0);
   

    while(1){
        //int16_t accelX = readAccelAxis(0x3B);
        int16_t accelY = readAccelAxis(0x3D);
        int16_t accelZ = readAccelAxis(0x3F);
        switch(tiltState) {
            case TILTED:
            //frownyFace(); 
            //changePiezoFrequency(2000);
            Serial.print("Tilted\n");
            break;
            case NORMAL:
            //smileyFace(); // smiley face
            if (abs(accelY) > THRESHOLD || abs(accelZ) > THRESHOLD) {
                tiltState = TILTED;
            }
            Serial.print("Normal\n");
            break;
        }
        
        /*if (abs(accelY) > THRESHOLD || abs(accelZ) > THRESHOLD) {
            tiltState = TILTED;
            Serial.print("Tilted\n");
        } else {
            tiltState = NORMAL;
            Serial.print("Normal\n");
        }*/

   
    if (tiltState == TILTED) {
        frownyFace(); 
       changeDutyCycle(1); //start buzzer
    } else {
        smileyFace(); // smiley face
    }
        switch(state) {
            case wait_press:
            

                break;
            case debounce_press:
                ms_delay(1);//Timer 0
                state = wait_release;

                break;
            case wait_release:
                
                break;
            case debounce_release:
                
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
        changeDutyCycle(0); // stop buzzer
        state = debounce_release; // Transition to debounce_release state
    }
}

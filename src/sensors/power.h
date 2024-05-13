#ifndef POWER_H
#define POWER_H

#include "../defs/hwdefs.h"
#include <math.h>
#include <Arduino.h>

float inputPower = 0, outputPower = 0, reflectedPower = 0,
        VSWR = 0;   //We also need to track VSWR, as this is sent to the head unit.

/**
 * Input Power Status Code
 * 
 * 0 / False: Input Power OK
 * 1 / True: Input Power Critical
*/
bool inputState = false;

/**
 * VSWR Status Code
 * 0: VSWR Acceptable
 * 1: VSWR Above Warning Threshold
 * 2: VSWR Too High - trigger overdrive switch
*/
unsigned short vswrState = false;

/**
 * @brief Converts given power in dBm to milliwatts.
 * 
 * @param dBm The power in dBm that we want to convert to milliwatts.
 * @returns The power in milliwatts.
 * 
*/
float dBm2mW(float dBm){
    return pow(10, (dBm / 10.0));
}

/**
 * @brief Takes a forward power and reflected power in milliwatts and finds the VSWR.
 * 
 * @param forward The forward power in milliwatts
 * @param reflected The reflected power in milliwatts.
 * @returns The VSWR.
*/
float vswr(float forward, float reflected){
    return (1 + sqrt(reflected / forward)) / (1 - sqrt(reflected / forward));
}

float lt5538_to_dBm(float reading){
    #if DEBUG == 1
        Serial.print("LT5538 Voltage Reading: ");
        Serial.print(reading);
        Serial.println (" V.");
    #endif
    return (reading - 1.7171) / 0.0209;
}

float adl5519_to_dBm(float reading){
    #if DEBUG == 1
        Serial.print("ADL5519 Voltage Reading: ");
        Serial.print(reading);
        Serial.println (" V.");
    #endif
    return (reading - 0.4598) / -0.0217;
}

void readPowerDetectors(){
    inputPower = lt5538_to_dBm(5.0 * (analogRead(INPUT_PD))/1023.0);
    outputPower = adl5519_to_dBm(5.0 * (analogRead(FORWARD_PD))/1023.0);
    reflectedPower = adl5519_to_dBm(5.0 * (analogRead(REFLECTED_PD))/1023.0);

    VSWR = vswr(dBm2mW(outputPower), dBm2mW(reflectedPower));
}

void setPowerStates(){
    if(VSWR >= VSWR_WARN){
        if(vswrState == 2){
            vswrState = 2;
        }
        else if(VSWR >= VSWR_MAX){
            vswrState = 2;
        }
        else{
            vswrState = 1;
        }
    }
    else vswrState = 0;

    if(inputPower >= INPUT_PWR_MAX)
        inputState = true;
    else inputState = false;
}

#endif
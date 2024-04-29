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
 * 0 / False: VSWR Acceptable
 * 1 / True: VSWR Too High - trigger overdrive switch
*/
bool vswrState = false;

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

float adl5519_to_dBm(float reading){
    return (reading / (-0.0215)) + 22.2158;
}

float lt5538_to_dBm(float reading){
    return 50.109 * reading - 86.318;
}

void readPowerDetectors(){
    inputPower = lt5538_to_dBm(analogRead(INPUT_PD));
    outputPower = adl5519_to_dBm(analogRead(FORWARD_PD));
    reflectedPower = adl5519_to_dBm(analogRead(REFLECTED_PD));

    VSWR = vswr(dBm2mW(outputPower), dBm2mW(reflectedPower));
}

void setPowerStates(){
    if(VSWR >= VSWR_MAX)
        vswrState = true;
    else vswrState = false;

    if(inputPower >= INPUT_PWR_MAX)
        inputState = true;
    else inputState = false;
}

#endif
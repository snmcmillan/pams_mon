#ifndef POWER_H
#define POWER_H

#include "../defs/hwdefs.h"
#include <math.h>

float inputPower = 0;
float outputPower = 0;
float reflectedPower = 0;

//We also need to track VSWR, as this is sent to the head unit.
float VSWR = 0;

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
    return pow(10, (dBm / 10));
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

#endif
#ifndef SENSORS_H
#define SENSORS_H
#include "../comms.h"

#include "../defs/hwdefs.h"
#include "../defs/swdefs.h"

#include "power.h"
#include "current.h"
#include "temperature.h"


#include<HardwareSerial.h>

/**
 * Overdrive Switch State
 * 
 * This boolean directly controls the overdrive switch state.
*/
bool overdriveState = false;

void initSensors(){
    initTempSensor();
}

void readSensors(){
    #if DEMO == 1
        temperature = (float) (rand()%10000) / 100;
        current = (float) (rand()%1000) / 100;
        inputPower = (float) (rand()%1000) / 100;
        outputPower = (float) (rand()%1000) / 100;
        reflectedPower = (float) (rand()%1000) / 100 - outputPower;
        VSWR = vswr(dBm2mW(outputPower), dBm2mW(reflectedPower));
    #else
        readTemperature();
        readCurrent();
        readPowerDetectors();
    #endif 
    #if DEBUG == 1
        Serial.println(temperature);
        Serial.println(current);
        Serial.println(inputPower);
        Serial.println(outputPower);
        Serial.println(reflectedPower);
        Serial.println(VSWR);
        delay(2000);
    #endif
}

void setStates(){
    setThermalState();
    setPowerStates();
}

void setOverdrive(){
    if(thermalState > 1 || inputState || vswrState)
        overdriveState = true;
    else overdriveState = false;

    if(overdriveState)
        digitalWrite(OVERDRIVE_P1, HIGH);
    else digitalWrite(OVERDRIVE_P1, LOW);
}

#endif
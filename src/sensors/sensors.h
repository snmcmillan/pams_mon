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
        reflectedPower = (float) (rand()%1000) / 100;
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
    #endif
}

void setStates(){
    setThermalState();
}

#endif
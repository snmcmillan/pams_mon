#ifndef CURRENT_H
#define CURRENT_H

#include "../defs/hwdefs.h"

#include <Arduino.h>

float current = 0;

float calculateCurrent(float reading){
    #if DEBUG == 1
        Serial.print("Current Sensor Voltage Reading: ");
        Serial.print(reading/1000);
        Serial.println (" mV.");
    #endif
    return CURRENT_SENSE_LIMIT * (reading / 4.0);
}

void readCurrent(){
    current = calculateCurrent(5.0 * (analogRead((CURRENT_SENSE))) / 1023.0);
}
#endif
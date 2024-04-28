#ifndef CURRENT_H
#define CURRENT_H

#include "../defs/hwdefs.h"

#include <Arduino.h>

float current = 0, currentSenseReading = 0;

float calculateCurrent(){
    return CURRENT_SENSE_LIMIT * (currentSenseReading / 4.0);
}

void readCurrent(){
    currentSenseReading = analogRead(CURRENT_SENSE);
    current = calculateCurrent();
}
#endif
#ifndef CURRENT_H
#define CURRENT_H

#include "../defs/hwdefs.h"

#include <Arduino.h>

float current = 0;

float calculateCurrent(float reading){
    return CURRENT_SENSE_LIMIT * (reading / 4.0);
}

void readCurrent(){
    current = calculateCurrent(analogRead(CURRENT_SENSE));
}
#endif
#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "../defs/hwdefs.h"

#include "Adafruit_MCP9808.h"

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

float temperature = 0;
unsigned long tempHighFirstTimestamp = 0; //If we go above the warn threshold, get this time stamp.

/**
 * Thermal Status Codes
 * 
 * 0: Temperature OK
 * 1: Temperature Warning
 * 2: Temperature Critical - Maximum Reached
 * 3: Temperature Critical - Above Warning Threshold for too long.
 * 4: Thermal Runaway Detected 
 * Conditions 2, 3, and 4 are critical.
*/
unsigned short thermalState = 0;

void initTempSensor(){
    tempsensor.begin(TEMP_SENSOR_I2C_ADDR);
    tempsensor.setResolution(1);
}

void readTemperature(){
    tempsensor.wake();
    temperature = tempsensor.readTempC();
    tempsensor.shutdown_wake(1);
}

float milliseconds2Seconds(unsigned long milliseconds){
    return milliseconds / 1000.0;
}

float seconds2Minutes(unsigned long seconds){
    return seconds / 60.0;
}

#endif
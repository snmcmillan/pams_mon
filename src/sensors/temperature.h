#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "../defs/hwdefs.h"

#include "Adafruit_MCP9808.h"

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

float temperature = 0, previousTemp = 0, deltaT = 0;
bool tempWarn = false;
unsigned long previousTempTimestamp = 0, currentTempTimeStamp = 0, 
            tempWarnTimestamp = 0, thermalRunawayTriggeredTimeStamp = 0;
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

unsigned long minutes2Milliseconds(int minutes){
    return minutes * 60000;
}

bool thermalRunaway(){
    if(deltaT > TEMP_DELTA_MAX){
        if(previousTemp == 0 && previousTempTimestamp == 0){ //Checks if this is the first run, if it is, we won't consider it thermal runaway.
            return false;                                    //Hypothetically speaking, this branch could trigger in a real runaway case, but that's almost impossible.
        }
        else{
            if(thermalState == 4) 
                thermalRunawayTriggeredTimeStamp = millis();
            return true;
            
        }
    }
    else if(thermalState == 4 && ((millis() - thermalRunawayTriggeredTimeStamp) < minutes2Milliseconds(THERMAL_RUNAWAY_COOLDOWN)))
        return true;
    else return false;
}

void shiftTemps(){
    previousTemp = temperature;
    previousTempTimestamp = currentTempTimeStamp;
}



float milliseconds2Seconds(unsigned long milliseconds){
    return milliseconds / 1000.0;
}

float seconds2Minutes(float seconds){
    return seconds / 60.0;
}

float milliseconds2Minutes(unsigned long milliseconds){
    return seconds2Minutes(milliseconds2Seconds(milliseconds));
}

void calculateDeltaT(){
    deltaT = (temperature - previousTemp)/(milliseconds2Minutes(currentTempTimeStamp - previousTempTimestamp));
}

void readTemperature(){
    shiftTemps();
    tempsensor.wake();
    temperature = tempsensor.readTempC();
    tempsensor.shutdown_wake(1);
    calculateDeltaT();
}

void setThermalState(){
    if(temperature > TEMP_UPPER_SOFT){
        if(thermalRunaway()){
            thermalState = 4;
        }
        else if(temperature > TEMP_UPPER_HARD){
            if(thermalRunaway()){
                thermalState = 4;
            }
            else thermalState = 2;
        }
        else{
            if(!tempWarn){
                thermalState = 1;
                tempWarn = true;
                tempWarnTimestamp = millis();
            }
            else{
                if((tempWarnTimestamp - previousTempTimestamp) >= minutes2Milliseconds(TEMP_TIME_LIMIT)){
                    thermalState = 3;
                }
            }
        }
    }
    else{
        if(thermalRunaway()){
            thermalState = 4;
        }
        else thermalState = 0;
    }
}


#endif
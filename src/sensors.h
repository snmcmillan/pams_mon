#ifndef SENSORS_H
#define SENSORS_H
#include "comms.h"
#include "defs/hwdefs.h"
#include "defs/swdefs.h"
#include<HardwareSerial.h>

//We're setting some convenient units conversions.
#define MINUTES_PER_SECOND 1/60
#define SECONDS_PER_MINUTE 60

#define SECONDS_PER_MILISECOND 1/1000
#define MILISECONDS_PER_SECOND 1000

float temperature = 0;
float current = 0;
float signalPower = 0;
float forwardPower = 0;
float reflectedPower = 0;

/**
 * State Codes
 *  2: Upper Threshold Critical
 *  1: Upper Threshold Warning
 *  0: OK
 * -1: Lower Threshold Warning
 * -2: Lower Threshold Critical
 * 
*/
int temperatureState = 0;
int currentState = 0;
int signalPowerState = 0;
int forwardPowerState = 0;
int reflectedPowerState = 0;

void readSensors(){
  #if DEMO == 1
    temperature = (float) (rand()%10000) / 100;
    current = (float) (rand()%1000) / 100;
    forwardPower = (float) (rand()%1000) / 100;
    reflectedPower = (float) (rand()%1000) / 100;
    signalPower = (float) (rand()%1000) / 100;
  #else
  #endif 
  #if DEBUG == 1
    Serial.println(temperature);
    Serial.println(current);
    Serial.println(signalPower);
    Serial.println(forwardPower);
    Serial.println(reflectedPower);
  #endif
}

#endif
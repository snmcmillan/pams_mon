

#ifndef COMMS_H
#define COMMS_H
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include "defs/swdefs.h"
#include "defs/hwdefs.h"
#include "sensors.h"

#include <Arduino.h>

SoftwareSerial monSerial = SoftwareSerial(MON_RX, MON_TX);

/**
 * waitForHead: Waits for any data to be sent from the head unit.
 * 
 * This variant does not discard any data. 
 * Once any data is read, execution continues.
*/
void waitForHead(){
  while(monSerial.peek() == -1){}
}

/**
 * waitForHead: Waits for the head unit to send the supplied code.
 * 
 * This variant discards all data until the specified code is read.
 * Once the code is read, it is also discarded.
*/
void waitForHead(int code){
  while(monSerial.read() != code){}
}

/**
 * acknowledgeHead: Sends a supplied status code to the head unit.
*/
void acknowledgeHead(int code){
  monSerial.write(code);
}

void sendReadings(){
  waitForHead(23);
  #if DEBUG == 1
    Serial.println("Head Unit Wants Data!");
  #endif
  monSerial.print(temperature);
  monSerial.print(current);
  monSerial.print(signalPower);
  monSerial.print(forwardPower);
  monSerial.print(reflectedPower);
  monSerial.print(temperatureState);
  monSerial.print(currentState);
  monSerial.print(signalPowerState);
  monSerial.print(forwardPowerState);
  monSerial.print(reflectedPowerState);

  #if DEBUG == 1
    Serial.println("Head Unit Read Data!");
  #endif
  monSerial.flush();
}

#endif


#ifndef COMMS_H
#define COMMS_H
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include "defs/swdefs.h"
#include "defs/hwdefs.h"
#include "sensors/sensors.h"



SoftwareSerial monSerial = SoftwareSerial(MON_RX, MON_TX);
String monName = MON_NAME;

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

void initMon(){
    monSerial.begin(BAUD_RATE);
    monSerial.flush();
    waitForHead(10);
    #if DEBUG == 1
        Serial.begin(9600);
        Serial.println("Head Unit Wants Data!");
    #endif
    monSerial.println(monName);
    waitForHead(20);
    monSerial.flush();
    #if DEBUG == 1
        Serial.println("Initial Handshake Performed!");
    #endif
}

void sendData(){
    waitForHead(23);
    #if DEBUG == 1
        Serial.println("Head Unit Wants Data!");
    #endif
    monSerial.print(temperature);
    monSerial.print(',');
    monSerial.print(current);
    monSerial.print(',');
    monSerial.print(inputPower);
    monSerial.print(',');
    monSerial.print(outputPower);
    monSerial.print(',');
    monSerial.print(VSWR);
    monSerial.print(',');
    monSerial.print(thermalState);
    monSerial.print(',');
    monSerial.print(inputState);
    monSerial.print(',');
    monSerial.print(vswrState);

    #if DEBUG == 1
        Serial.println("Head Unit Read Data!");
    #endif
    monSerial.flush();
}

#endif
#include "hwdefs.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
#if DEMO == 1
  #include <time.h>
#endif

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

String monName = MON_NAME;

SoftwareSerial monSerial = SoftwareSerial(MON_RX, MON_TX);

void waitForHead(int code){
  while(monSerial.read() != code){}
  monSerial.read();
}

void acknowledgeHead(int code){
  monSerial.write(code);
}

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

void setErrorStates(){

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

void setup() {
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

void loop() {
  readSensors();
  //setErrorStates();
  sendReadings();
}


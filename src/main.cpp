#include "defs/hwdefs.h"
#include "defs/swdefs.h"
#include "comms.h"
#include "sensors.h"
#if DEMO == 1
  #include <time.h>
#endif

String monName = MON_NAME;


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
  sendReadings();
}


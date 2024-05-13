#include "defs/hwdefs.h"
#include "defs/swdefs.h"
#include "comms.h"
#include "sensors/sensors.h"
#if DEMO == 1
  #include <time.h>
#endif
void setup() {
  pinMode(OVERDRIVE_P2, OUTPUT);
  digitalWrite(OVERDRIVE_P2, LOW);
  initSensors();
  initMon();
}

void loop() {
  readSensors();
  setStates();
  
  setOverdrive();
  sendData();
}


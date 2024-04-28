#include "defs/hwdefs.h"
#include "defs/swdefs.h"
#include "comms.h"
#include "sensors.h"
#if DEMO == 1
  #include <time.h>
#endif
void setup() {
  initMon();
}

void loop() {
  readSensors();
  sendReadings();
}


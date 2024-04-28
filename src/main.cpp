#include "defs/hwdefs.h"
#include "defs/swdefs.h"
#include "comms.h"
#include "sensors/sensors.h"
#if DEMO == 1
  #include <time.h>
#endif
void setup() {
  initSensors();
  initMon();

}

void loop() {
  readSensors();
  sendReadings();
}


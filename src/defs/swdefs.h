/**
 * swdefs.h - Software Configuration
 * 
 * These are flags that one can set to alter the program mode. These changes are applied at compile time.
*/
#ifndef SWDEFS_H
#define SWDEFS_H
/**
 * Demo Mode
 * 
 * Setting this to 1 disables the reading of sensors and instead generates completely random data.
 * This is for when we want to test production mode of the head unit, but don't want to have the sensor board fully populated.
 * This does still require serial connections to a head unit.
 * 
 * Setting this to 0 makes the program run normally, and read data from the sensors.
*/
#define DEMO 0


/**
 * Debug Mode
 * Setting this to 1 enables serial communication to a computer over USB.
 * This will enable one to monitor program flow without hooking up a debugger, and also displays all readings.
 * 
 * Having this enables does negatively impact performance, so only enable this if there are issues with the system.
*/
#define DEBUG 1

#endif
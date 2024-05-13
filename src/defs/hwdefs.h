/**
 * hwdefs.h - Hardware Definitions
 * 
 * This file specifies pins used by all hardware components used, as well as define the baud rate used for the connection to the monitor unit.
 * 
 * This file also defines the name of this monitor, as well as the various thresholds.
*/
#ifndef HWDEFS_H
#define HWDEFS_H

/**
 * Current Sensor Variant
 * 
 * We are using the HCT-0016 sensor, and we can easily adapt our sensing code to each variant.
 * 
 * There are the following variants of the HCT-0016, each with their own:
 *      -005 : 5 Amps       |   5
 *      -010 : 10 Amps      |   10
 *      -020 : 20 Amps      |   20
 *      -025 : 25 Amps      |   25
 *      -050 : 50 Amps      |   50
 *      -100 : 100 Amps     |   100
 * 
 * To set the correct variant, use the value on the right-hand side of the above list.
*/
#define CURRENT_SENSE_LIMIT 5

/*************************
 * Pinouts
 * 
 * All pinouts are going to be defined here.
**************************/

//Monitor-to-Head-Unit Serial pins
#define MON_RX 5
#define MON_TX 6

//Current Sensor Pin
#define CURRENT_SENSE A0



/**
 * Temperature Sensor Pins
 * 
 * The temperature sensor is I2C, so while we don't define the pins, here are what they are on the Arduino Uno:
 * 
 * SDA : A4
 * SCL : A5
 * 
 * We can, however, define the I2C address of the sensor.
*/
#define TEMP_SENSOR_I2C_ADDR 0x18

/**
 * Power Detector Pins
 * 
 * This should be self explanatory.
 * 
 * Reminder: our setup uses 2 ICs:
 *      - LT5538 : Single Channel Power Detector used on the input.
 *      - ADL5519 : Dual Channel Power Detector used on the output for both forward and reflected power.
*/
#define INPUT_PD A1

#define INPUT_SCALE 360/157

#define FORWARD_PD A2
#define REFLECTED_PD A3

/**
 * Overdrive Switch Control Pins
 * 
 * We're defining both control pins.
*/
#define OVERDRIVE_P1 3
#define OVERDRIVE_P2 2

/***********************
 * Monitoring Settings
 * 
 * Monitor name, baud rate, and sensor thresholds are defined here.
************************/

//Monitor-to-Head-Unit Baud Rate - Ensure this matches the head unit
#define BAUD_RATE 9600

//Monitor Display Name
#define MON_NAME "Monitor 1 Demo"

/**
 * Temperature Thresholds
 * 
 * All temperatures are in Celsius, and all times are in minutes.
 * 
 * TEMP_UPPER_SOFT : Above this temperature, we'll see a warning, 
 *                   and if it sits above this for a time length TEMP_TIME_LIMIT, shuts down the PA.
 * 
 * TEMP_UPPER_HARD : At or above this temperature, we will shut down the PA.
 * 
 * TEMP_TIME_LIMIT : If we are above TEMP_UPPER_SOFT for this long, we shut down the PA.
 * 
 * TEMP_DELTA_MAX  : If our change in temperature (in degrees Celsius/minute) exceeds this,
 *                   we will shut down the PA.
*/
#define TEMP_UPPER_SOFT 70 //Degrees Celsius
#define TEMP_UPPER_HARD 80 //Degrees Celsius
#define TEMP_TIME_LIMIT 5 //Minutes
#define TEMP_DELTA_MAX 1 //Degrees Celsius Per Minute

#define THERMAL_RUNAWAY_COOLDOWN 5 //Minutes

#define INPUT_PWR_MAX 10 //dBm

#define VSWR_WARN 3.5
#define VSWR_MAX 4.0


#endif
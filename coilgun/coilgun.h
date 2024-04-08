#ifndef COILGUN_H
#define COILGUN_H

#include <arduino.h>
#include <string.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

bool SAFETY_STATE =      0; // 0 = safe (discharge gun), 1 = fire (normal operation)
#define COIL_NUM                  6
#define VOLT_ADC_MIN              0
#define VOLT_ADC_MAX              1024
const int MAX_VOLT =            350;
const int MIN_VOLT =            0;

const int REFRESH_TIME = 1000;            // time to refresh the Nextion page every 100 ms
unsigned long refresh_timer = millis();  // timer for refreshing Nextion's page
const int REFRESH_TIME2 = 1000;           // time to refresh the Nextion page every 100 ms
unsigned long refresh_timer2 = millis(); // timer for refreshing Nextion's page

// -------- PIN DEFINITIONS --------

//Charge Board
#define CHARGE_TOGGLE       2
#define FAULT               3
#define DONE                4

//Relay Board
#define DISCHARGE_TOGGLE    11
#define VOLTAGE_SENS        14
#define RELAY_TOGGLE        12

//HMI and other
#define TRIGGER             16
#define SAFETY_SWITCH       15
#define LCD_SERIAL          Serial1
#define LCD_TX              1
#define LCD_RX              0
#define LED_DATA            7
#define MAX_BRIGHTNESS      70
#define LED_COUNT           3
Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(LED_COUNT, LED_DATA);
#define SERVO               8
Servo fire_servo;


//Coil Boards
#define COIL1               22
#define COIL2               21
#define COIL3               20
#define COIL4               19
#define COIL5               18
#define COIL6               17

void interrupt();
void charge();
void discharge();
void coilFire();
int readVoltage();
void LCDRead();
void LCDWrite();

#endif
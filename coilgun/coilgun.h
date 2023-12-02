#ifndef COILGUN_H
#define COILGUN_H

#include <arduino.h>

volatile bool SAFETY_STATE =      0; // 0 = safe (discharge gun), 1 = fire (normal operation)
#define COIL_NUM                  2
#define VOLT_ADC_MIN              30
#define VOLT_ADC_MAX              1023
const float MAX_VOLT =            400;
const float TARGET_VOLT =         350;
const float MIN_VOLT =            0;

// -------- PIN DEFINITIONS --------
#define CHARGING_LED        5
#define CHARGED_LED         8
#define DISCHARGING_LED     11
#define CHARGE_ENABLE       15
#define DISCHARGE_ENABLE    17
#define OPTICAL_SENS_1      23
#define OPTICAL_SENS_2      22
#define TRIGGER             2
#define SAFETY_SWITCH       3
#define LCD_SERIAL          Serial1
#define LCD_TX              1
#define LCD_RX              0
#define VOLTAGE_SENS        20
#define COIL1               21
#define COIL2               18

void interrupt();
void charge();
void discharge(bool fullDischarge);
void Edischarge();
void coilFire();
float readVoltage();

#endif
#ifndef COILGUN_H
#define COILGUN_H

#include <arduino.h>

#define SAFETY_STATE        0 // 0 = safe (discharge gun), 1 = fire (normal operation)
#define COIL_NUM            2
#define VOLT_ADC_MIN        0
#define VOLT_ADC_MAX        4096
const float MAX_VOLT = 400;
const float TARGET_VOLT = 350;
const float MIN_VOLT = 0;

// -------- PIN DEFINITIONS --------
#define CHARGING_LED        5
#define CHARGED_LED         8
#define DISCHARING_LED      10
#define CHARGE_ENABLE       15
#define DISCHARGE_ENABLE    16
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

void charge();
void discharge(bool fullDischarge);
void coilFire();
float readVoltage();

#endif
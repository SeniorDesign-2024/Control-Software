#include "coilgun.h"

void setup ()
{
  pinMode(CHARGING_LED, OUTPUT);
  digitalWrite(CHARGING_LED, LOW);

  pinMode(CHARGED_LED, OUTPUT);
  digitalWrite(CHARGED_LED, LOW);

  pinMode(DISCHARING_LED, OUTPUT);
  digitalWrite(DISCHARING_LED, LOW);

  pinMode(CHARGE_ENABLE, OUTPUT);
  digitalWrite(CHARGE_ENABLE, LOW);

  pinMode(DISCHARGE_ENABLE, OUTPUT);
  digitalWrite(DISCHARGE_ENABLE, LOW);

  pinMode(OPTICAL_SENS_1, INPUT_PULLUP);

  pinMode(OPTICAL_SENS_2, INPUT_PULLUP);

  pinMode(TRIGGER, INPUT_PULLUP);

  pinMode(SAFETY_SWITCH, INPUT_PULLUP);

  LCD_SERIAL.begin(9600);

  pinMode(VOLTAGE_SENS, INPUT);

  pinMode(COIL1, OUTPUT);
  digitalWrite(COIL1, LOW);

  pinMode(COIL2, OUTPUT);
  digitalWrite(COIL2, LOW);

  Serial.begin(9600); 
}

void loop ()
{
  



  /*  LED Test Code
  digitalWrite(COIL1, HIGH);
  digitalWrite(COIL2, HIGH);
  digitalWrite(CHARGING_LED, HIGH);
  digitalWrite(CHARGED_LED, HIGH);
  digitalWrite(DISCHARING_LED, HIGH);
  digitalWrite(CHARGE_ENABLE, HIGH);
  digitalWrite(DISCHARGE_ENABLE, HIGH);
  delay(1000);
  Serial.println("ON");
  digitalWrite(COIL1, LOW);
  digitalWrite(COIL2, LOW);
  digitalWrite(CHARGING_LED, LOW);
  digitalWrite(CHARGED_LED, LOW);
  digitalWrite(DISCHARING_LED, LOW);
  digitalWrite(CHARGE_ENABLE, LOW);
  digitalWrite(DISCHARGE_ENABLE, LOW);
  delay(1000);
  Serial.println("OFF");
  */
}

void charge()
{
  bool charging = false;
  float voltage = 0;

  while (1)
  {
    if (SAFETY_STATE == 0)
    {
      return;
    }
    
    voltage = readVoltage();
    if (voltage >= MAX_VOLT)
    {
      discharge(false);
      return;
    }

    if (voltage >= TARGET_VOLT)
      return;
    else if (!charging) 
    {
      digitalWrite(CHARGING_LED, HIGH);
      digitalWrite(CHARGE_ENABLE, HIGH);
    }
  }
}

void discharge(bool fullDischarge)
{
  
}

void coilFire()
{
  
}

float readVoltage()
{
  float voltage = 0;
  voltage = map(analogRead(VOLTAGE_SENS), VOLT_ADC_MIN, VOLT_ADC_MAX, MIN_VOLT, MAX_VOLT);
  return voltage;
}
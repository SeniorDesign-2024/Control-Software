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

  //LCD_SERIAL.begin(9600);

  pinMode(VOLTAGE_SENS, INPUT);

  pinMode(COIL1, OUTPUT);
  digitalWrite(COIL1, LOW);

  pinMode(COIL2, OUTPUT);
  digitalWrite(COIL2, LOW);

  Serial.begin(9600); 
}

void loop ()
{
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

}
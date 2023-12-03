#include "coilgun.h"
#include <string.h>



void setup ()
{
  pinMode(CHARGING_LED, OUTPUT);
  digitalWrite(CHARGING_LED, LOW);

  pinMode(CHARGED_LED, OUTPUT);
  digitalWrite(CHARGED_LED, LOW);

  pinMode(DISCHARGING_LED, OUTPUT);
  digitalWrite(DISCHARGING_LED, LOW);

  pinMode(CHARGE_ENABLE, OUTPUT);
  digitalWrite(CHARGE_ENABLE, LOW);

  pinMode(DISCHARGE_ENABLE, OUTPUT);
  digitalWrite(DISCHARGE_ENABLE, LOW);

  pinMode(OPTICAL_SENS_1, INPUT_PULLUP);

  pinMode(OPTICAL_SENS_2, INPUT_PULLUP);

  pinMode(TRIGGER, INPUT_PULLUP);

  pinMode(SAFETY_SWITCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SAFETY_SWITCH), interrupt, RISING);

  LCD_SERIAL.begin(115200);

  pinMode(VOLTAGE_SENS, INPUT);

  pinMode(COIL1, OUTPUT);
  digitalWrite(COIL1, LOW);

  pinMode(COIL2, OUTPUT);
  digitalWrite(COIL2, LOW);

  Serial.begin(115200); 
}

void interrupt()
{
  digitalWrite(CHARGING_LED, LOW);
  digitalWrite(CHARGED_LED, LOW);
  digitalWrite(DISCHARGING_LED, LOW);
  digitalWrite(CHARGE_ENABLE, LOW);
  digitalWrite(DISCHARGE_ENABLE, LOW);

  SAFETY_STATE = 0;
  Edischarge();
}

void loop ()
{

  if (!digitalRead(SAFETY_SWITCH))
  {
    SAFETY_STATE = true;
  }
  if (SAFETY_STATE)
  {
    int volt = readVoltage();
    Serial.println(volt);
    if (volt>=TARGET_VOLT)
      digitalWrite(CHARGED_LED, HIGH);
    else
      digitalWrite(CHARGED_LED, LOW);
    LCD_SERIAL.print("n0.val=");
    LCD_SERIAL.print(volt);
    LCDWrite();
    LCDRead();

    if (!digitalRead(TRIGGER) && (readVoltage()>=TARGET_VOLT))
    {
      coilFire();
    }
    
    
    
    //charge();
   // discharge(false);
    //if (readVoltage()>30)
    //  discharge(true);
  }
  
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

void LCDRead ()
{
  if (LCD_SERIAL.available()) 
  {
    command = LCD_SERIAL.readStringUntil('\n');
    command.trim(); 
    Serial.print("Received Command: ");
    Serial.println(command);
  }
}

void LCDWrite ()
{
  LCD_SERIAL.print(0xff);
  LCD_SERIAL.print(0xff);
  LCD_SERIAL.print(0xff);
}

void charge()
{
  bool charging = false;
  int voltage = 0;

  while (1)
  {
    if (SAFETY_STATE == 0)
    {
      digitalWrite(CHARGING_LED, LOW);
      digitalWrite(CHARGE_ENABLE, LOW);
      return;
    }
    
    voltage = readVoltage();
    if (voltage >= MAX_VOLT)
    {
      discharge(false);
      return;
    }

    if (voltage >= TARGET_VOLT)
    {
      digitalWrite(CHARGING_LED, LOW);
      digitalWrite(CHARGE_ENABLE, LOW);
      return;
    } 
    else if (!charging) 
    {
      digitalWrite(CHARGING_LED, HIGH);
      digitalWrite(CHARGE_ENABLE, HIGH);
      charging = true;
    }
  }
}

void discharge(bool fullDischarge)
{
  bool discharging = false;
  int voltage = 0;

  while (1)
  {
    if (SAFETY_STATE == 0)
    {
      digitalWrite(DISCHARGING_LED, LOW);
      digitalWrite(DISCHARGE_ENABLE, LOW);
      return;
    }
    
    voltage = readVoltage();
    if (fullDischarge)  // discharge to 0
    {
      if(!discharging)
      {
        digitalWrite(DISCHARGING_LED, HIGH);
        digitalWrite(DISCHARGE_ENABLE, HIGH);
        discharging = true;
      }
      if (voltage <= (MIN_VOLT+10))
      {
        digitalWrite(DISCHARGING_LED, LOW);
        digitalWrite(DISCHARGE_ENABLE, LOW);
        return;
      } 
    }
    else if (!fullDischarge) // go to target voltage in case of over charging
    {
      if(!discharging)
      {
        digitalWrite(DISCHARGING_LED, HIGH);
        digitalWrite(DISCHARGE_ENABLE, HIGH);
        discharging = true;
      }
      else if (voltage <= TARGET_VOLT)
      {
        digitalWrite(DISCHARGING_LED, LOW);
        digitalWrite(DISCHARGE_ENABLE, LOW);
        return;
      } 
    }
    
  }
}

void Edischarge()
{
  bool discharging = false;
  int voltage = 0;
  voltage = readVoltage();
  if(!discharging)
  {
    digitalWrite(DISCHARGING_LED, HIGH);
    digitalWrite(DISCHARGE_ENABLE, HIGH);
    discharging = true;
  }
  if (voltage <= (MIN_VOLT+10))
  {
    digitalWrite(DISCHARGING_LED, LOW);
    digitalWrite(DISCHARGE_ENABLE, LOW);
    return;
  } 
}

void coilFire()
{
  cli();
  digitalWrite(COIL1, HIGH);
  while(digitalRead(OPTICAL_SENS_1));
  digitalWrite(COIL1, LOW);
  digitalWrite(COIL2, HIGH);
  while(digitalRead(OPTICAL_SENS_2));
  digitalWrite(COIL2, LOW);
  sei();
}

int readVoltage()
{
  int voltage = 0;
  voltage = map(analogRead(VOLTAGE_SENS), VOLT_ADC_MIN, VOLT_ADC_MAX, MIN_VOLT, MAX_VOLT);
  return voltage;
}
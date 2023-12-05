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
  //attachInterrupt(digitalPinToInterrupt(SAFETY_SWITCH), interrupt, FALLING);

  Serial1.begin(115200);

  pinMode(VOLTAGE_SENS, INPUT);

  pinMode(COIL1, OUTPUT);
  digitalWrite(COIL1, LOW);

  pinMode(COIL2, OUTPUT);
  digitalWrite(COIL2, LOW);

  Serial.begin(115200); 
}

void interrupt()
{
    Serial.println("interrupt");
    digitalWrite(CHARGING_LED, LOW);
    digitalWrite(CHARGED_LED, LOW);
    digitalWrite(DISCHARGING_LED, LOW);
    digitalWrite(CHARGE_ENABLE, LOW);
    digitalWrite(DISCHARGE_ENABLE, LOW);
    Serial1.print("t3.bco=63488");
    Serial1.print("\xFF\xFF\xFF");
    Edischarge();
  SAFETY_STATE = 0;
}



void loop ()
{
  
  int volt = readVoltage();                          // a variable to store the reading

  if (!digitalRead(SAFETY_SWITCH))
  {
    SAFETY_STATE = 1;
    Serial1.print("t3.bco=1632");
    Serial1.print("\xFF\xFF\xFF");
  }
  else if (digitalRead(SAFETY_SWITCH))
  {
    digitalWrite(CHARGING_LED, LOW);
    digitalWrite(CHARGED_LED, LOW);
    digitalWrite(DISCHARGING_LED, LOW);
    digitalWrite(CHARGE_ENABLE, LOW);
    digitalWrite(DISCHARGE_ENABLE, LOW);
    Serial1.print("t3.bco=63488");
    Serial1.print("\xFF\xFF\xFF");
    Edischarge();
    SAFETY_STATE = 0;
  }
  if (SAFETY_STATE)
  {
    if (volt>=TARGET_VOLT)
      digitalWrite(CHARGED_LED, HIGH);
    else
      digitalWrite(CHARGED_LED, LOW);

    
    bool trigger_state = digitalRead(TRIGGER);
    if (!trigger_state && (volt>=TARGET_VOLT))
    {
      coilFire();
    }
    LCDRead();
    LCDWrite();

      
    
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


void charge()
{
  bool charging = false;
  int voltage = 0;

  while (1)
  {
    LCDWrite();
    if (digitalRead(SAFETY_SWITCH))
    {
      digitalWrite(CHARGING_LED, LOW);
      digitalWrite(CHARGED_LED, LOW);
      digitalWrite(DISCHARGING_LED, LOW);
      digitalWrite(CHARGE_ENABLE, LOW);
      digitalWrite(DISCHARGE_ENABLE, LOW);
      Serial1.print("t3.bco=63488");
      Serial1.print("\xFF\xFF\xFF");
      Edischarge();
      SAFETY_STATE = 0;
    }
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
    LCDWrite();
    if (digitalRead(SAFETY_SWITCH))
    {
      digitalWrite(CHARGING_LED, LOW);
      digitalWrite(CHARGED_LED, LOW);
      digitalWrite(DISCHARGING_LED, LOW);
      digitalWrite(CHARGE_ENABLE, LOW);
      digitalWrite(DISCHARGE_ENABLE, LOW);
      Serial1.print("t3.bco=63488");
      Serial1.print("\xFF\xFF\xFF");
      Edischarge();
      SAFETY_STATE = 0;
    }
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
  
  while(1)
  {
    LCDWrite();
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
  
}

void coilFire()
{
  digitalWrite(COIL1, HIGH);
  while(digitalRead(OPTICAL_SENS_1));
  digitalWrite(COIL1, LOW);
  digitalWrite(COIL2, HIGH);
  while(digitalRead(OPTICAL_SENS_2));
  digitalWrite(COIL2, LOW);
}

int readVoltage()
{
  int voltage = 0;
  voltage = map(analogRead(VOLTAGE_SENS), VOLT_ADC_MIN, VOLT_ADC_MAX, MIN_VOLT, MAX_VOLT);
  return voltage;
}

void LCDRead()
{
  String command;
  if ((millis() - refresh_timer2) > REFRESH_TIME2)
  {
    if (Serial1.available())
    {
      command = Serial1.readStringUntil('\n');
      command.trim();
      Serial.print("Received Command: ");
      Serial.println(command);

      if (command.equals("DIS"))
      {
        discharge(true);
      }
      if (command.equals("CHG"))
      {
        charge();
      }
    }
  }    
}

void LCDWrite()
{
  if ((millis() - refresh_timer) > REFRESH_TIME)
  { // IMPORTANT do not have serial print commands in the loop without a delay
    //  or an if statement with a timer condition like this one.

    int volt = analogRead(VOLTAGE_SENS);                // Read the analog pin
    volt = map(volt, 0, 1022, 0, 400);    // same like: voltage = analogRead(A0)*5000/1024
    //voltagebar = map(volt, 0, 1022, 0, 400); // same like: voltage = analogRead(A0)*5000/1024
    /* We Re-map the value of volt from 0-1024 (steps) to 0-5000 millivolt
    * connect the pins of a Potentiometer on A0 pin, 5v (5000 millivolt) and GND. Outer pins to 5v and GND, middle pin to A0
    * https://www.arduino.cc/en/tutorial/potentiometer
    * Turn it over and read values from 0 to 5000 millivolts
    */
    Serial1.print("n0.val=");
    Serial1.print(volt);
    Serial1.print("\xFF\xFF\xFF");
    //Serial1.print("j0.val=");
    //Serial1.print(voltagebar);
    //Serial1.print("\xFF\xFF\xFF");     


    refresh_timer = millis(); // Set the timer equal to millis, create a time stamp to start over the "delay"
  }
}
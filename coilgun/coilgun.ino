#include "coilgun.h"



void setup ()
{
  pinMode(CHARGE_TOGGLE, OUTPUT);
  digitalWrite(CHARGE_TOGGLE, LOW);
  
  pinMode(FAULT, INPUT);
  
  pinMode(DONE, INPUT);

  pinMode(DISCHARGE_TOGGLE, OUTPUT);
  digitalWrite(DISCHARGE_TOGGLE, LOW);

  pinMode(VOLTAGE_SENS, INPUT);
  
  pinMode(RELAY_TOGGLE, OUTPUT);
  digitalWrite(RELAY_TOGGLE, LOW);
  
  pinMode(TRIGGER, INPUT_PULLUP);

  pinMode(SAFETY_SWITCH, INPUT_PULLUP);

  //Serial1.begin(115200);
  //fire_servo.attach(SERVO, 0, 2500);
  //neoPixel.begin();
  //neoPixel.setBrightness(MAX_BRIGHTNESS);
  
  pinMode(COIL1, OUTPUT);
  digitalWrite(COIL1, LOW);

  pinMode(COIL2, INPUT_PULLUP);
  //digitalWrite(COIL2, LOW);
  
  pinMode(COIL3, OUTPUT);
  digitalWrite(COIL3, LOW);

  pinMode(COIL4, OUTPUT);
  digitalWrite(COIL4, LOW);
  
  pinMode(COIL5, OUTPUT);
  digitalWrite(COIL5, LOW);

  pinMode(COIL6, OUTPUT);
  digitalWrite(COIL6, LOW);

  Serial.begin(115200); 
}

void loop ()
{
  if (digitalRead(TRIGGER) != 1)
  {
    delay(5);
    while(digitalRead(TRIGGER) != 1)
    {}
    Serial.println("FIRE");
    digitalWrite(COIL1, HIGH);
    Serial.println("HIGH");
    delayMicroseconds(40);
    digitalWrite(COIL1, LOW);
    Serial.println("LOW");
  }
  if(!digitalRead(SAFETY_SWITCH))
  {
    digitalWrite(CHARGE_TOGGLE, HIGH);
    while(!digitalRead(SAFETY_SWITCH));   
    digitalWrite(CHARGE_TOGGLE, LOW);
  }
  if(!digitalRead(COIL2))
  {
    while(!digitalRead(COIL2))
    {
      digitalWrite(CHARGE_TOGGLE, LOW);
      digitalWrite(DISCHARGE_TOGGLE, HIGH);
    }
    
    digitalWrite(DISCHARGE_TOGGLE, LOW);
  }
}
  /* this code for actual gun
  int volt = readVoltage();                          // a variable to store the reading

  if (!digitalRead(SAFETY_SWITCH))
  {
    SAFETY_STATE = 1;
    Serial1.print("t3.bco=1632");
    Serial1.print("\xFF\xFF\xFF");
  }
  else if (digitalRead(SAFETY_SWITCH))
  {
    Serial1.print("t3.bco=63488");
    Serial1.print("\xFF\xFF\xFF");
    discharge();
    SAFETY_STATE = 0;
  }
  if (SAFETY_STATE)
  {    
    bool trigger_state = digitalRead(TRIGGER);
    if (!trigger_state)
    {
      coilFire();
    }
    LCDRead();
    LCDWrite();
  }
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
      digitalWrite(CHARGE_TOGGLE, LOW);
      digitalWrite(DISCHARGE_TOGGLE, LOW);
      Serial1.print("t3.bco=63488");
      Serial1.print("\xFF\xFF\xFF");
      discharge();
      SAFETY_STATE = 0;
    }
    if (SAFETY_STATE == 0)
    {
      digitalWrite(CHARGE_TOGGLE, LOW);
      charging = false;
      return;
    }
    
    voltage = readVoltage();

    if (voltage >= MAX_VOLT)
    {
      digitalWrite(CHARGE_TOGGLE, LOW);
      charging = false;
      return;
    } 
    else if (!charging) 
    {
      digitalWrite(CHARGE_TOGGLE, HIGH);
      charging = true;
    }
  }
}

void discharge()
{
  bool discharging = false;
  int voltage = 0;

  while (1)
  {
    LCDWrite();
    if (digitalRead(SAFETY_SWITCH))
    {
      digitalWrite(CHARGE_TOGGLE, LOW);
      digitalWrite(DISCHARGE_TOGGLE, LOW);
      Serial1.print("t3.bco=63488");
      Serial1.print("\xFF\xFF\xFF");
      discharge();
      SAFETY_STATE = 0;
    }
    if (SAFETY_STATE == 0)
    {
      digitalWrite(DISCHARGE_TOGGLE, LOW);
      return;
    }
    
    voltage = readVoltage();
    if(!discharging)
    {
      digitalWrite(DISCHARGE_TOGGLE, HIGH);
      discharging = true;
    }
    if (voltage <= (MIN_VOLT+10))
    {
      digitalWrite(DISCHARGE_TOGGLE, LOW);
      return;
    }    
  }
}
 
void coilFire()
{
  digitalWrite(COIL1, HIGH);
  delayMicroseconds(3);
  digitalWrite(COIL1, LOW);

  digitalWrite(COIL2, HIGH);
  delayMicroseconds(3);
  digitalWrite(COIL2, LOW);

  digitalWrite(COIL3, HIGH);
  delayMicroseconds(3);
  digitalWrite(COIL3, LOW);

  digitalWrite(COIL4, HIGH);
  delayMicroseconds(3);
  digitalWrite(COIL4, LOW);

  digitalWrite(COIL5, HIGH);
  delayMicroseconds(3);
  digitalWrite(COIL5, LOW);

  digitalWrite(COIL6, HIGH);
  delayMicroseconds(3);
  digitalWrite(COIL6, LOW);
}
*/
int readVoltage()
{
  int voltage = 0;
  voltage = map(analogRead(VOLTAGE_SENS), VOLT_ADC_MIN, VOLT_ADC_MAX, MIN_VOLT, MAX_VOLT);
  return voltage;
}
/*
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
        discharge();
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
  { 
    int volt = readVoltage();
    Serial1.print("n0.val=");
    Serial1.print(volt);
    Serial1.print("\xFF\xFF\xFF");
    refresh_timer = millis();
  }
}*/
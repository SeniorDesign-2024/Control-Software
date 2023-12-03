
String command;
int voltage;                             // a variable to store the reading
int voltagebar;                          // a variable to store the reading
const int REFRESH_TIME = 500;            // time to refresh the Nextion page every 100 ms
unsigned long refresh_timer = millis();  // timer for refreshing Nextion's page
const int REFRESH_TIME2 = 100;           // time to refresh the Nextion page every 100 ms
unsigned long refresh_timer2 = millis(); // timer for refreshing Nextion's page

void setup()
{
  pinMode(20, INPUT);
  Serial1.begin(115200);
  Serial.begin(115200);
}

void loop()
{
  if ((millis() - refresh_timer) > REFRESH_TIME)
  { // IMPORTANT do not have serial print commands in the loop without a delay
    //  or an if statement with a timer condition like this one.

    int tempData = analogRead(20);                // Read the analog pin
    voltage = map(tempData, 30, 1023, 0, 400);    // same like: voltage = analogRead(A0)*5000/1024
    voltagebar = map(tempData, 30, 1023, 0, 100); // same like: voltage = analogRead(A0)*5000/1024
    /* We Re-map the value of tempData from 0-1024 (steps) to 0-5000 millivolt
     * connect the pins of a Potentiometer on A0 pin, 5v (5000 millivolt) and GND. Outer pins to 5v and GND, middle pin to A0
     * https://www.arduino.cc/en/tutorial/potentiometer
     * Turn it over and read values from 0 to 5000 millivolts
     */

    Serial1.print("n0.val=");
    Serial1.print(voltage);
    Serial1.print("\xFF\xFF\xFF");
    Serial1.print("j0.val=");
    Serial1.print(voltagebar);
    Serial1.print("\xFF\xFF\xFF");

    refresh_timer = millis(); // Set the timer equal to millis, create a time stamp to start over the "delay"
  }

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
        Serial1.print("t3.bco=1632");
        Serial1.print("\xFF\xFF\xFF");
      }
      if (command.equals("CHG"))
      {
        Serial1.print("t3.bco=63488");
        Serial1.print("\xFF\xFF\xFF");
      }
    }
  }
}

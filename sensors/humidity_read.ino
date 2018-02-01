// Arduino script to read humidity sensor relative humidity output

int analogPin = 0;    // Humidity sensor connected to analog pin 0
int val = 0;          // Variable to store bin values
float voltage = 0;    // Variable to store voltage
int RH = 0;           // Relative humidity

void setup()
{
  Serial.begin(9600);   // Setup serial connection
}

void loop()
{
  val = analogRead(analogPin);        // Read input pin voltage
  voltage = (float)3.3*(val/1024);    // Conversion to voltage [V]
  RH = 0.0062*(voltage/5 - 0.16);         // Conversion to % relative humidity
  Serial.println(RH);                 // Print value to terminal
}

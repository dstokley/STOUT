// Humidity sensor variables
int analogPin = 0;    // Humidity sensor connected to analog pin 0
int val;          // Variable to store bin values
float voltage;    // Variable to store voltage
float RH;           // Relative humidity
unsigned long previousMillis = 0; // Time of last update
const long interval = 1000; // Measurement interval [ms]

void setup()
{
  // Set up serial connection with UDOO
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

// Loop function which takes and transmits humidity sensor data at 1 Hz
void loop()
{
  unsigned long currentMillis = millis(); // Read current time
  unsigned int val;
  // Check if it has been 1 second since last measurement
  if (currentMillis - previousMillis >= interval)
  {
  val = analogRead(analogPin);            // Read input pin voltage
  Serial.print(val);
   //byte * b = (byte *) &val;                // Create byte pointer for RH
  //Serial.write(b, 4);                     // Send all 4 bytes to UDOO
  //voltage = (float)3.3*(val/1024);        // Conversion to voltage [V]
  //RH = (float)0.0062*(voltage/5 - 0.16);  // Conversion to % relative humidity
  previousMillis = currentMillis;         // Reset time stamp

  // Send RH to Braswell via serial
  //byte * b = (byte *) &RH;                // Create byte pointer for RH
  //Serial.write(b, 4);                     // Send all 4 bytes to UDOO

  }
}

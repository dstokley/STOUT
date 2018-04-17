// Script for carrying out all required Arduino functionality. The tasks which occur include:
// measuring pressure, humidity, and internal/external temperature at a rate of 1 Hz throughout
// the whole mission, reading GPS time when possible, and sending this data to the UDOO to update
// its clock every minute, performing required actuations for the horizontal and vertical linear
// actuators when new attitude data is received from the UDOO, and signaling the UDOO to start
// taking spectrometer measurments when the actuations are complete. In addition, this program 
// checks the encoders for the linear actuators during actuation to ensure that the correct number
// of steps are taken. If the counts are off, the required actuations are updated and completed. 
//
// Inputs:  Horizontal and vertical linear actuations required to move optics train to point at 
//          desired location. These are transmitted to the Arduino via the serial connection with
//          the UDOO. The bytes are read into the float values step_x and step_y.
//          
//          GPIO interrupt based on state change from UDOO GPIO pin 347. This interrupt is used to
//          trigger the start of linear actuations.
//
// Outputs: Pressure, humidity, 5 internal temperatures, 2 external temperatures, and GPS timing
//          data to the UDOO via the serial connection at a rate of 1 Hz.
//
//          GPIO interrupt based on state change sent to UDOO GPIO pin 349. This interrupt is used
//          to signal the end of actuations and start spectrometer integration on the UDOO.

// Required Libraries
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GPS.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <math.h>             

// Define pins for convienence
// Horizontal linear actuator
#define EN_x 8                // Horizontal enable pin
#define DIR_x 9               // Horizontal step pin
#define STP_x 10              // Horizontal direction pin
// Vertical linear actuator
#define EN_y 11               // Vertical enable pin
#define DIR_y 12              // Vertical step pin
#define STP_y 13              // Vertical direction pin
// Interrupts
#define INTRPT1 14            // Interrupt for receiving actuation values from UDOO GPIO 347
#define INTRPT2 15            // Interrupt for sending actuation complete to UDOO GPIO 349
#define SEALEVELPRESSURE_HPA (1013.25)
// Heater Control
#define H1 A0
#define H2 A1
// I2C (Pressure/Humidity/Temp Sensor)
#define BME_MISO A4
#define BME_SCK A5

// Declare variables for actuation use
float step_x = 0;            // Required horizontal actuation distance [mm]
float step_y = 0;            // Required vertical actuation distance [mm]
float step_size = 1.5e-3;    // Step size of actuators [mm]
int stepact_x;               // Number of horizontal steps & direction (+/-)
int stepact_y;               // Number of vertical steps & direction (+/-)
int stepnum_x;               // Number of horizontal actuation steps
int stepnum_y;               // Number of vertical actuation steps
int remsteps_x;              // Remaining horizontal actuation steps
int remsteps_y;              // Remaining vertical actuation steps

// Sensor reading variables
unsigned long previousMillis = 0; // Time of last update
const long interval = 1000; // Measurement interval [ms]

// Communication protocol for BME280 sensor
Adafruit_BME280 bme; // I2C

// GPS 
HardwareSerial* mySerial = &Serial1;
Adafruit_GPS GPS(mySerial);

void setup()
{
  Serial.print("here");
  // Set up serial connection with UDOO
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Set up interrupts
  pinMode(INTRPT1, INPUT);      // Set interrupt pin to an input
  // Attach interrupt to ISR (occurs on change in state)
  attachInterrupt(digitalPinToInterrupt(INTRPT1), controlsISR, CHANGE);

  // Set all relevant digital pins to outputs for motor control
  // Horizontal actuator motor driver
  pinMode(EN_x, OUTPUT);
  pinMode(STP_x, OUTPUT);
  pinMode(DIR_x, OUTPUT);
  // Vertical actuator motor driver
  pinMode(EN_y, OUTPUT);
  pinMode(STP_y, OUTPUT);
  pinMode(DIR_y, OUTPUT);

  // GPIO pin for signaling interrupt on the UDOO (change in state)
  pinMode(INTRPT2, OUTPUT);

  // Setup pressure/humidity sensor
  bool status;
  // Default settings
  status = bme.begin();  
  if (!status) {
      // Check for wiring error
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }
  
  // Setup internal/external temperature sensors
  dallas(2,1);
  dallas(3,1);
  dallas(4,1);
  dallas(5,1);
  dallas(6,1);
  dallas(7,1);

  // Setup GPS
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);

  // Enable/Disable interrupts
  noInterrupts();

}

// Loop function which takes and transmits EMCS data at 1 Hz
void loop()
{
  unsigned long currentMillis = millis(); // Read current time
  // Check if it has been 1 second since last measurement
  if (currentMillis - previousMillis >= interval)
  {
    byte data_array[24];
    // Tranmist all collected data to UDOO
    msg_transmit(data_array);
    previousMillis = currentMillis;         // Reset time stamp
  }
  
}


void controlsISR()
{
  byte temp_var[4]; 
  
  // Read incoming serial data & save in step_x and step_y
 for (int i=0; i<4; i++)
  {
    temp_var[i] = Serial.read();
  }
  memcpy(&step_x, &temp_var, sizeof step_x);    // Save bytes to create a float

  for (int i=0; i<4; i++)
  {
    temp_var[i] = Serial.read();
  }
  memcpy(&step_y, &temp_var, sizeof step_y);    // Save bytes to create a float
  
  // Calculate necessary numbers of steps and dirction for hoizontal and vertical actuations
  // Horizontal linear actuator
  if (step_x > 0.0)
  {
    digitalWrite(DIR_x, HIGH);                  // Positive actuation
  }
  else
  {
    digitalWrite(DIR_x, LOW);                  // Negative actuation
  }

  stepact_x = (int)ceil(step_x/step_size);          // Actual integer of required steps (can be negative or positive)
  stepnum_x = (int)ceil(fabs(step_x)/step_size);    // Positive integer of required steps
  remsteps_x = stepnum_x;                           // Extra variable for decrementing

  // Vertical linear actuator
  if (step_y > 0.0)
  {
    digitalWrite(DIR_y,HIGH);                  // Positive actuation
  }
  else
  {
    digitalWrite(DIR_y, LOW);                  // Negative actuation
  }

  stepact_y = (int)ceil(step_y/step_size);          // Actual integer of required steps (can be negative or positive)
  stepnum_y = (int)ceil(fabs(step_y)/step_size);    // Positive integer of required steps
  remsteps_y = stepnum_y;                           // Extra variable for decrementing

  // Actuate both motors simultaneously
  // Stay in this loop until all actuations are completed

  // Enable movement for both actuators
  digitalWrite(EN_x, LOW);
  digitalWrite(EN_y, LOW);

  while(remsteps_x != 0 || remsteps_y != 0)
  {
    // Actuations are required for both motors
    if (remsteps_x != 0 && remsteps_y != 0)
    {
      // Trigger one step foward for each actuator
      digitalWrite(STP_x, HIGH);
      digitalWrite(STP_y, HIGH);

      delayMicroseconds(100); // Delay appropriate amount of time

      // Reset to allow for more actuations
      digitalWrite(STP_x, LOW);
      digitalWrite(STP_y, LOW);

      // Subtract from number of steps
      remsteps_x--;
      remsteps_y--;

      delayMicroseconds(100); // Delay appropriate amount of time
    }

    // Actuations are only required for the horizontal motor
    else if (remsteps_x != 0 && remsteps_y == 0)
    {
      // Trigger one step foward for horizontal actuator
      digitalWrite(STP_x, HIGH);

      delayMicroseconds(100); // Delay appropriate amount of time

      // Reset to allow for more actuations
      digitalWrite(STP_x, LOW);

      // Subtract from number of steps
      remsteps_x--;

      delayMicroseconds(100); // Delay appropriate amount of time
    }

    // Actuations are only required for the vertical motor
    else if (remsteps_x == 0 && remsteps_y != 0)
    {
      // Trigger one step foward for vertical actuator
      digitalWrite(STP_y, HIGH);

      delayMicroseconds(100); // Delay appropriate amount of time

      // Reset to allow for more actuations
      digitalWrite(STP_y, LOW);

      // Subtract from number of steps
      remsteps_y--;

      delayMicroseconds(100); // Delay appropriate amount of time
    }

  }

   // Disable movement for both actuators
  digitalWrite(EN_x, HIGH);
  digitalWrite(EN_y, HIGH);

  // Send done signal to UDOO (GPIO state change)
  // Change state of output
  digitalWrite(INTRPT2, !digitalRead(INTRPT2));
}


// Function to setup internal and external temperature sensors(OneWire protocol)
int16_t dallas(int x,byte start)
{
  OneWire ds(x);
  byte i;
  byte data[4];
  int16_t result;
  do
  {
    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);
    for (i=0; i<2; i++) data[i] = ds.read();
    result = (data[1]<<8)|data[0];
    result>>=4; if (data[1]&128) result|=61440;
    if (data[0]&8) ++result;
    ds.reset();
    ds.write(0xCC);
    ds.write(0x44,1);
    if (start) delay(1000);
  } while (start--);
  return result;
}


// Send all environmental sensor data to the main UDOO processor via the serial connection
void msg_transmit(byte data_array[]){
  
  bool GPS_data;
  
  // Add internal temperature values to the data array
  data_array[0] = (byte)((dallas(2,0))&0xFF);             // Four 1-wire internal temperature sensors
  data_array[1] = (byte)(((dallas(2,0))>>8)&0xFF);
  data_array[2] = (byte)((dallas(3,0))&0xFF);
  data_array[3] = (byte)(((dallas(3,0))>>8)&0xFF);
  data_array[4] = (byte)((dallas(4,0))&0xFF);
  data_array[5] = (byte)(((dallas(4,0))>>8)&0xFF);
  data_array[6] = (byte)((dallas(5,0))&0xFF);
  data_array[7] = (byte)(((dallas(5,0))>>8)&0xFF);

  int bme_temp = (int)(round(bme.readTemperature()));     // BME280 temperature reading
  data_array[8] = (byte)(bme_temp&0xFF);
  data_array[9] = (byte)((bme_temp>>8)&0xFF);

  // Add external temperature values to the data array
  data_array[10] = (byte)((dallas(6,0))&0xFF);  // Two 1-wire external temperature sensors
  data_array[11] = (byte)(((dallas(6,0))>>8)&0xFF);
  data_array[12] = (byte)((dallas(7,0))&0xFF);
  data_array[13] = (byte)(((dallas(7,0))>>8)&0xFF);

   // Add pressure and humidity values to data array
  long bme_press = (long)(round(bme.readPressure()));     // BME280 pressure reading
  data_array[14] = (byte)(bme_press&0xFF);
  data_array[15] = (byte)((bme_press>>8)&0xFF);
  data_array[16] = (byte)((bme_press>>16)&0xFF);
  data_array[17] = (byte)((bme_press>>24)&0xFF);

  int bme_humid = (int)(round(bme.readHumidity()));     // BME280 humidity reading
  data_array[18] = (byte)(bme_humid&0xFF);
  data_array[19] = (byte)((bme_humid>>8)&0xFF);

  // Check if a GPS lock has been acheived, add data to data array if it has
  GPS.read();
  if (GPS.newNMEAreceived()) {
    GPS.parse(GPS.lastNMEA());  
   }
  // If a GPS fix is obtained, add data to array
  if (GPS.fix) {
    data_array[20] = (byte)(GPS.hour);
    data_array[21] = (byte)(GPS.minute);
    data_array[22] = (byte)(GPS.seconds);
    int GPS_ms = (int)(GPS.milliseconds);
    data_array[23] = (byte)(GPS_ms&0xFF);
    data_array[24] = (byte)((GPS_ms>>8)&0xFF);
    
    GPS_data = true;
       }
   // Otherwise don't add data to array
   else {
    GPS_data = false;
   }

   // Send correct number of bytes to UDOO
   if (GPS_data) {
    Serial.write(data_array, 25);
   }
   else {
    Serial.write(data_array, 20);
   }
}

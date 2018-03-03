// GPS STUFF ------------------------------------------
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
HardwareSerial mySerial = Serial1;
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  true
boolean usingInterrupt = false;
void useInterrupt(boolean);
// ----------------------------------------------------

void setup() {
// GPS STUFF ------------------------------------------
Serial.begin(115200);
Serial.println("Adafruit GPS library basic test!");
GPS.begin(115200);
GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);  
GPS.sendCommand(PGCMD_ANTENNA);
useInterrupt(true);
delay(1000);
mySerial.println(PMTK_Q_RELEASE);
// ----------------------------------------------------

}

void loop() {
  // put your main code here, to run repeatedly:

}

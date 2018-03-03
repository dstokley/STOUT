#include <Adafruit_GPS.h>
HardwareSerial* mySerial = &Serial1;
Adafruit_GPS GPS(mySerial);

void setup()
{
   Serial.begin(115200);
   Serial.println("Adafruit GPS library basic test!");
   GPS.begin(9600);
   GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
   GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
   GPS.sendCommand(PGCMD_ANTENNA);
   delay(1000);
   mySerial->println(PMTK_Q_RELEASE);
}

void loop()                   
{
   GPS.read();
   if (GPS.newNMEAreceived()) {
      if (!GPS.parse(GPS.lastNMEA()))   
         return;
   }

   if (GPS.fix) {
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
   }

   else {
    Serial.println("\nNo GPS Fix");
   }
}

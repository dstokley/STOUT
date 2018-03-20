#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK A5
#define BME_MISO A4

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

// Timing check
unsigned long t1, t2;

void setup() {
    Serial.begin(115200);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    }

    // Setup pressure/humidity sensor
    bool status;
    // default settings
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }

    // Setup internal temperature sensors
    dallas(2,1);
    dallas(3,1);
    dallas(4,1);
    dallas(5,1);
    dallas(6,1);
    dallas(7,1);
    
}

void loop() {
      t1 = millis();
      
      printPress();     // Print temp, press, alt, and humidity from BME280

      printIntTemp();   // Print internal temp values

      t2 = millis();

      Serial.println();
      Serial.println(t2-t1);

      delay(1000);
     
}

void printPress() {
//    Serial.print("Temperature = ");
//    Serial.print(bme.readTemperature());
//    Serial.println(" *C");
//
//    Serial.print("Pressure = ");
//    Serial.print(bme.readPressure() / 100.0F);
//    Serial.println(" hPa");
//
//    Serial.print("Approx. Altitude = ");
//    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
//    Serial.println(" m");
//
//    Serial.print("Humidity = ");
//    Serial.print(bme.readHumidity());
//    Serial.println(" %");
//
//    Serial.println();
}

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

void printIntTemp() {
//    Serial.print("Int Temperature 1 = ");
//    Serial.print(dallas(2,0),HEX);
//    Serial.println(" *C");
//
//    Serial.print("Int Temperature 2 = ");
//    Serial.print(dallas(3,0),HEX);
//    Serial.println(" *C");
//
//    Serial.print("Int Temperature 3 = ");
//    Serial.print(dallas(4,0),HEX);
//    Serial.println(" *C");
//
//    Serial.print("Int Temperature 4 = ");
//    Serial.print(dallas(5,0),HEX);
//    Serial.println(" *C");
//
//    Serial.print("Ext Temperature 1 = ");
//    Serial.print(dallas(6,0));
//    Serial.println(" *C");
//
//    Serial.print("Ext Temperature 2 = ");
//    Serial.print(dallas(7,0));
//    Serial.println(" *C");
//
//    Serial.println();

    char data_array[8];
    // Add internal temperature values to the data array
    data_array[0] = (byte)((dallas(2,0))&0xFF);             // Four 1-wire internal temperature sensors
    data_array[1] = (byte)(((dallas(2,0))>>8)&0xFF);
    data_array[2] = (byte)((dallas(3,0))&0xFF);
    data_array[3] = (byte)(((dallas(3,0))>>8)&0xFF);
    data_array[4] = (byte)((dallas(4,0))&0xFF);
    data_array[5] = (byte)(((dallas(4,0))>>8)&0xFF);
    data_array[6] = (byte)((dallas(5,0))&0xFF);
    data_array[7] = (byte)(((dallas(5,0))>>8)&0xFF);

    delay(10);
//    data_array[0] = 0;
//    data_array[1] = 1;
//     data_array[2] = 0;
//    data_array[3] = 1;
//     data_array[4] = 0;
//    data_array[5] = 1;
//     data_array[6] = 0;
//    data_array[7] = 1;

    int bytes_written = Serial.write(data_array, 8);
    Serial.println(bytes_written);

}

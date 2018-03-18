#include <OneWire.h>

int16_t dallas(int x, byte start)
{
  OneWire ds(x);
  byte i;
  byte data[2];
  int16_t result;
  do
  {
    ds.reset();
    ds.write(0xCC);
    ds.write(0xBE);
    for (i = 0; i < 2; i++) data[i] = ds.read();
    result = (data[1] << 8) | data[0];
    result >>= 4; if (data[1] & 128) result |= 61440;
    if (data[0] & 8) ++result;
    ds.reset();
    ds.write(0xCC);
    ds.write(0x44, 1);
    if (start) delay(1000);
  }
  while (start--);
  return result;
}

void setup() {
  Serial.begin(115200);
  dallas(A3, 1);
  //dallas(A5,1);

}

void loop() {
  delay(1000);
  Serial.println(dallas(A3, 0));
  //Serial.println(dallas(A5,0));
}

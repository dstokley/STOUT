byte inByte;

boolean received = false;   // store if Arduino received something

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial port at a baud rate of 115200 bps
  Serial.begin(115200);
  delay(100);
  Serial.println("start");
}

#define RCVSIZE 8

void loop() {
  // put your main code here, to run repeatedly: 
  byte msg[RCVSIZE];
  int count = 0;
  
  while (Serial.available() > 0) {
    
    // get the new byte:
    byte inByte = (byte)Serial.read();
    Serial.println(inByte);
    msg[count] = inByte;
    count++;
    //delay(1);
    received = true;
   
  }
  
  if(received) {
    Serial.println();
    byte send_msg[] = {1,2,3,4,5,6,7,8};
    Serial.write(send_msg, 8);
    received = false;

  }
  
}

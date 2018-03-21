void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
}

void loop() {
  float step_x, step_y;
   byte temp_var[4]; 
  
  // Read incoming serial data & save in step_x and step_y
 for (int i=0; i<4; i++)
  {
    temp_var[i] = Serial.read();
  }
  memcpy(&step_x, &temp_var, sizeof step_x);    // Save bytes to create a float
  
  Serial.println(step_x);

  for (int i=0; i<4; i++)
  {
    temp_var[i] = Serial.read();
  }
  memcpy(&step_y, &temp_var, sizeof step_y);    // Save bytes to create a float

}

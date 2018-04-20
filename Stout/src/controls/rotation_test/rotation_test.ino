 //Declare pin functions on Redboard
#define stp_h 10
#define dir_h 9
#define EN_h  8

#define stp_v 13
#define dir_v 12
#define EN_v  11

//Declare variables for functions
unsigned int x;


void setup() {
  // put your setup code here, to run once:
  pinMode(stp_h, OUTPUT);
  pinMode(dir_h, OUTPUT);
  pinMode(EN_h, OUTPUT);
  pinMode(stp_v, OUTPUT);
  pinMode(dir_v, OUTPUT);
  pinMode(EN_v, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(dir_v, LOW); //Pull direction pin low to move "backward"
  for(x= 1; x<=500; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_v,HIGH); //Trigger one step forward
    delayMicroseconds(250);
    digitalWrite(stp_v,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(250);
  }
  
  delay(1000);
  
  digitalWrite(dir_h, LOW); //Pull direction pin low to move "backward"
  for(x= 1; x<=500; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_h,HIGH); //Trigger one step forward
    delayMicroseconds(250);
    digitalWrite(stp_h,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(250);
  }

  delay(1000);

  digitalWrite(dir_v, HIGH); //Pull direction pin low to move "backward"
  for(x= 1; x<=500; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_v,HIGH); //Trigger one step forward
    delayMicroseconds(250);
    digitalWrite(stp_v,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(250);
  }

  delay(1000);

  digitalWrite(dir_h, HIGH); //Pull direction pin low to move "backward"
  for(x= 1; x<=500; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_h,HIGH); //Trigger one step forward
    delayMicroseconds(250);
    digitalWrite(stp_h,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(250);
  }

  delay(1000);
  
  
}

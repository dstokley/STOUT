 #include <EEPROM.h>
 
 //Declare pin functions on Redboard
#define stp_h 10
#define dir_h 9
#define EN_h  8

#define stp_v 13
#define dir_v 12
#define EN_v  11


//Declare variables for functions
char user_input;
String user_input_steps;
unsigned int x;
int state;
long hor_pos=0, vert_pos=0;
unsigned int num_steps;

//Reset Easy Driver pins to default states
void resetEDPins()
{
  digitalWrite(stp_h, LOW);
  digitalWrite(dir_h, LOW);
  digitalWrite(EN_h, HIGH);

  digitalWrite(stp_v, LOW);
  digitalWrite(dir_v, LOW);
  digitalWrite(EN_v, HIGH);
}

//Default microstep mode function
void StepForwardDefault1()
{
  Serial.println("Enter desired number of steps:");
  while(1)
  {
    if(Serial.available())
    {
     user_input_steps = Serial.readString();
     delay(1);
     num_steps = user_input_steps.toInt();
     Serial.println(num_steps);
     break;
    }
  }
  
  Serial.println("Moving forward at default step mode.");
  digitalWrite(dir_h, HIGH); //Pull direction pin low to move "forward"
  for(x= 1; x<=num_steps; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_h,HIGH); //Trigger one step forward
    delayMicroseconds(250);
    digitalWrite(stp_h,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(250);
  }
  hor_pos = hor_pos + num_steps;
  Serial.println();
  Serial.print("Horizontal steps from starting point:");
  Serial.println(hor_pos);
  Serial.print("Vertical steps from starting point:");
  Serial.println(vert_pos);
  Serial.println();
  Serial.println("Enter new option");
  Serial.println();
}

//Backward microstep mode function
void StepBackwardDefault1()
{
   Serial.println("Enter desired number of steps:");
  while(1)
  {
    if(Serial.available())
    {
     user_input_steps = Serial.readString();
     delay(1);
     num_steps = user_input_steps.toInt();
     Serial.println(num_steps);
     break;
    }
  }
  Serial.println("Moving backward at default step mode.");
  digitalWrite(dir_h, LOW); //Pull direction pin low to move "backward"
  for(x= 1; x<=num_steps; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_h,HIGH); //Trigger one step forward
    delayMicroseconds(250);
    digitalWrite(stp_h,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(250);
  }
  hor_pos = hor_pos - num_steps;
  Serial.println();
  Serial.print("Horizontal steps from starting point:");
  Serial.println(hor_pos);
  Serial.print("Vertical steps from starting point:");
  Serial.println(vert_pos);
  Serial.println();
  Serial.println("Enter new option");
  Serial.println();
}

//Default microstep mode function
void StepForwardDefault2()
{
   Serial.println("Enter desired number of steps:");
  while(1)
  {
    if(Serial.available())
    {
     user_input_steps = Serial.readString();
     delay(1);
     num_steps = user_input_steps.toInt();
     Serial.println(num_steps);
     break;
    }
  }
  Serial.println("Moving forward at default step mode.");
  digitalWrite(dir_v, HIGH); //Pull direction pin low to move "forward"
  for(x= 1; x<=num_steps; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_v,HIGH); //Trigger one step forward
    delayMicroseconds(250);
    digitalWrite(stp_v,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(250);
  }
  vert_pos = vert_pos + num_steps;
  Serial.println();
  Serial.print("Horizontal steps from starting point:");
  Serial.println(hor_pos);
  Serial.print("Vertical steps from starting point:");
  Serial.println(vert_pos);
  Serial.println();
  Serial.println("Enter new option");
  Serial.println();
}

//Backward microstep mode function
void StepBackwardDefault2()
{
   Serial.println("Enter desired number of steps:");
  while(1)
  {
    if(Serial.available())
    {
     user_input_steps = Serial.readString();
     delay(1);
     num_steps = user_input_steps.toInt();
     Serial.println(num_steps);
     break;
    }
  }
  Serial.println("Moving backward at default step mode.");
  digitalWrite(dir_v, LOW); //Pull direction pin low to move "backward"
  for(x= 1; x<=num_steps; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp_v,HIGH); //Trigger one step forward
    delayMicroseconds(250);
    digitalWrite(stp_v,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(250);
  }
  vert_pos = vert_pos - num_steps;
  Serial.println();
  Serial.print("Horizontal steps from starting point:");
  Serial.println(hor_pos);
  Serial.print("Vertical steps from starting point:");
  Serial.println(vert_pos);
  Serial.println();
  Serial.println("Enter new option");
  Serial.println();
}

void setup() {
  pinMode(stp_h, OUTPUT);
  pinMode(dir_h, OUTPUT);
  pinMode(EN_h, OUTPUT);
  pinMode(stp_v, OUTPUT);
  pinMode(dir_v, OUTPUT);
  pinMode(EN_v, OUTPUT);
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control");
  Serial.println();
  //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. Turn at default microstep mode (horizontal motor)");
  Serial.println("2. Reverse direction at default microstep mode (horizontal motor)");
  Serial.println("3. Turn at default microstep mode (vertical motor)");
  Serial.println("4. Reverse direction at default microstep mode (vertical motor)");
  Serial.println();

}

void loop() {
    while(Serial.available()){
      user_input = Serial.read(); //Read user input and trigger appropriate function
      digitalWrite(EN_h, LOW); //Pull enable pin low to allow motor control
      digitalWrite(EN_v, LOW); //Pull enable pin low to allow motor control
      if (user_input =='1')
      {
         StepForwardDefault1();
      }
      else if (user_input =='2')
      {
         StepBackwardDefault1();
               }
      else if (user_input == '3')
      {
         StepForwardDefault2();
               }
      else if (user_input == '4')
      {
         StepBackwardDefault2();
      }
      else
      {
        Serial.println("Invalid option entered.");
      }
      resetEDPins();

}
}






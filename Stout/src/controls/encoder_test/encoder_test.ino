#define EN_x 8                // Horizontal enable pin
#define DIR_x 9               // Horizontal step pin
#define STP_x 10              // Horizontal direction pin
// Vertical linear actuator
#define EN_y 11               // Vertical enable pin
#define DIR_y 12              // Vertical step pin
#define STP_y 13              // Vertical direction pin

#define CH1_x A0              // Horizontal encoder channel 1
#define CH2_x A1              // Horizontal encoder channel 2
// Vertical encoder
#define CH1_y A2              // Vertical encoder channel 1
#define CH2_y A3              // Vertical encoder channel 2

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

// Declare variables for current/previous state of encoder channel 1 and counters
int ch1state_x;
int ch1state_y;
int ch1laststate_x;
int ch1laststate_y;
int counter_x = 0;
int counter_y = 0;


void setup() {
    // Set up serial connection with UDOO
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // put your setup code here, to run once:
   // Set all relevant digital pins to outputs for motor control
  // Horizontal actuator motor driver
  pinMode(EN_x, OUTPUT);
  pinMode(STP_x, OUTPUT);
  pinMode(DIR_x, OUTPUT);
  // Vertical actuator motor driver
  pinMode(EN_y, OUTPUT);
  pinMode(STP_y, OUTPUT);
  pinMode(DIR_y, OUTPUT);


  // Set all relevant pins to inputs for encoder readings
  pinMode(CH1_x, INPUT);      // Horizontal encoder
  pinMode(CH2_x, INPUT);
  pinMode(CH1_y, INPUT);      // Vertical encoder
  pinMode(CH2_y, INPUT);

  // Read current states of channel 1 on both encoders
  ch1laststate_x = digitalRead(CH1_x);
  ch1laststate_y = digitalRead(CH1_y);
  step_x = 1500e-3;
  step_y = 0;

  unsigned long t1, t2;

    // put your main code here, to run repeatedly:
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

      // Checking encoders
      ch1state_x = digitalRead(CH1_x);    // Current value on ch1 of horizontal encoder
      if(ch1state_x != ch1laststate_x)
      {
        if (digitalRead(CH2_x) != ch1state_x)
        {
          counter_x++;                    // Increment x encoder counter
        }
        else
        {
          counter_x--;                    // Decrement x encoder counter
        }
      }
      ch1laststate_x = ch1state_x;        // Save current value of encoder

      ch1state_y = digitalRead(CH1_y);    // Current value on ch1 of vertical encoder
      if(ch1state_y != ch1laststate_y)
      {
        if (digitalRead(CH2_y) != ch1state_y)
        {
          counter_y++;                    // Increment y encoder counter
        }
        else
        {
          counter_y--;                    // Decrement y encoder counter
        }
      }
      ch1laststate_y = ch1state_y;        // Save current value of encoder

      // Reset to allow for more actuations
      digitalWrite(STP_x, LOW);
      digitalWrite(STP_y, LOW);

      // Subtract from number of steps
      remsteps_x--;
      remsteps_y--;
    }

    // Actuations are only required for the horizontal motor
    else if (remsteps_x != 0 && remsteps_y == 0)
    {
      //Serial.println(remsteps_x);
      // Trigger one step foward for horizontal actuator
       //t1 = micros();
      digitalWrite(STP_x, HIGH);
      delayMicroseconds(94);
      // Checking horizontal encoder
      ch1state_x = digitalRead(CH1_x);    // Current value on ch1 of horizontal encoder
      if (ch1state_x != ch1laststate_x)
      {
        if (digitalRead(CH2_x) != ch1state_x)
        {
          counter_x++;                    // Increment x encoder counter
        }
        else
        {
          counter_x--;                    // Decrement x encoder counter
        }
      }
      ch1laststate_x = ch1state_x;        // Save current value of encoder
      //t2 = micros();
      //Serial.println(t2-t1);
      // Reset to allow for more actuations
      digitalWrite(STP_x, LOW);
      delayMicroseconds(100);

      // Subtract from number of steps
      remsteps_x--;
      Serial.println(counter_x);
    }

    // Actuations are only required for the vertical motor
    else if (remsteps_x == 0 && remsteps_y != 0)
    {
      // Trigger one step foward for vertical actuator
      digitalWrite(STP_y, HIGH);

      ch1state_y = digitalRead(CH1_y);    // Current value on ch1 of vertical encoder
      if(ch1state_y != ch1laststate_y)
      {
        if (digitalRead(CH2_y) != ch1state_y)
        {
          counter_y++;                    // Increment y encoder counter
        }
        else
        {
          counter_y--;                    // Decrement y encoder counter
        }
      }
      ch1laststate_y = ch1state_y;        // Save current value of encoder

      // Reset to allow for more actuations
      digitalWrite(STP_y, LOW);

      // Subtract from number of steps
      remsteps_y--;
          }

    // Check if required actuations were carried out by looking at encoder values when
    // remaining steps for horizontal and vertical actuation are both 0
    else if (remsteps_x == 0 && remsteps_y == 0)
    {
      
      //Serial.println(stepact_x);
      // Check for correct horizontal actuation
      if (counter_x != stepact_x)
      {
        if (abs(counter_x) > abs(stepact_x))
        {
          // Change actuation direction
          digitalWrite(DIR_x, !digitalRead(DIR_x));
          // Update remaining steps
          remsteps_x = abs(counter_x - stepact_x);
        }
        else if (abs(counter_x) < abs(stepact_x))
        {
          // Maintain actuation direction
          // Update remaining steps
          remsteps_x = abs(counter_x - stepact_x);
        }
      }
      // Check for correct vertical actuation
      else if (counter_y != stepact_y)
      {
        if (abs(counter_y) > abs(stepact_y))
        {
          // Change actuation direction
          digitalWrite(DIR_y, !digitalRead(DIR_y));
          // Update remaining steps
          remsteps_y = abs(counter_y - stepact_y);
        }
        else if (abs(counter_y) < abs(stepact_y))
        {
          // Maintain actuation direction
          // Update remaining steps
          remsteps_y = abs(counter_y - stepact_y);
        }
      }
    }
    //Serial.println(remsteps_x);
    //Serial.println(counter_x);
  }
}

void loop() {
  


   // Disable movement for both actuators
  digitalWrite(EN_x, HIGH);
  digitalWrite(EN_y, HIGH);
}

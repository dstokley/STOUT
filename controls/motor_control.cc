// Motor control function for each of the two Big Easy Drivers and their
// correpsonding linear actuators. Receives calculated actuation distances from
// the Braswell processor and implements these actuations. This control is
// interrupt driven to allow it to interrupt the humidity sensor readings at any
// point.
#include <math.h>             // Math function library
#include <EEPROM.h>           // EEPROM library

// Define pins for convienence
// Horizontal linear actuator
#define EN_x 2                // Horizontal enable pin
#define STP_x 3               // Horizontal step pin
#define DIR_x 4               // Horizontal direction pin
// Vertical linear actuator
#define EN_y 5                // Vertical enable pin
#define STP_y 6               // Vertical step pin
#define DIR_y 7               // Vertical direction pin
// Horizontal encoder
#define CH1_x 8               // Horizontal encoder channel 1
#define CH2_x 9               // Horizontal encoder channel 2
// Vertical encoder
#define CH1_y 10              // Vertical encoder channel 1
#define CH2_y 11              // Vertical encoder channel 2

// Declare variables for actuation use
float step_x;                // Required horizontal actuation distance [m]
float step_y;                // Required vertical actuation distance [m]
float step_size = 1.5e-6;    // Step size of actuators [m]
int stepact_x;               // Number of horizontal steps & direction (+/-)
int stepact_y;               //  Number of vertical steps & direction (+/-)
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

void setup()
{
  // Set all relevant digital pins to outputs for motor control
  // Horizontal actuator motor driver
  pinmode(EN_x, OUTPUT);
  pinmode(STP_x, OUTPUT);
  pinmode(DIR_x, OUTPUT);
  // Vertical actuator motor driver
  pinmode(EN_x, OUTPUT);
  pinmode(STP_x, OUTPUT);
  pinmode(DIR_x, OUTPUT);

  resetEDPins();              // Reset all pins to their default values

  // Set all relevant digital pins to inputs for encoder readings
  pinmode(CH1_x, INPUT);      // Horizontal encoder
  pinmode(CH2_x, INPUT);
  pinmode(CH1_y, INPUT);      // Vertical encoder
  pinmode(CH2_y, INPUT);

  // Read current states of channel 1 on both encoders
  ch1laststate_x = digitalRead(CH1_x);
  ch1laststate_y = digitalRead(CH1_y);

}

// Retrieve actuation values from global variables
// step_x = globalvar1;
// step_y = globalvar2;

// Calculate necessary numbers of steps and dirction for hoizontal and vertical
// actuations
// Horizontal linear actuator
if (step_x > 0)
{
  DIR_x = 1;                  // Positive actuation
}
else
{
  DIR_x = 0;                  // Negative actuation
}

stepact_x = (int)ceil(step_x/step_size);          // Actual integer of required steps
stepnum_x = (int)ceil(fabs(step_x)/step_size);    // Positive integer of required steps
remsteps_x = stepnum_x;                           // Extra variable for decrementing

// Vertical linear actuator
if (step_y > 0)
{
  DIR_y = 1;                  // Positive actuation
}
else
{
  DIR_y = 0;                  // Negative actuation
}

stepact_y = (int)ceil(step_y/step_size);          // Actual integer of required steps
stepnum_y = (int)ceil(fabs(step_y)/step_size);    // Integer of required steps
remsteps_y = stepnum_y;                           // Extra variable for decrementing

// Actuate both motors simultaneously
// Stay in this loop until all actuations are completed
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
    // Trigger one step foward for horizontal actuator
    digitalWrite(STP_x, HIGH);

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

    // Reset to allow for more actuations
    digitalWrite(STP_x, LOW);

    // Subtract from number of steps
    remsteps_x--;
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
    // Check for correct horizontal actuation
    if (counter_x != stepact_x)
    {
      if (abs(counter_x) > abs(stepact_x))
      {
        switch (DIR_x)
        {
          case 0:
            DIR_x = 1;
            break;
          case 1:
            DIR_x = 0;
            break;
        }
        remsteps_x = abs(counter_x - stepact_x);
      }
      else if (abs(counter_x) < abs(stepact_x))
      {
        remsteps_x = abs(counter_x - stepact_x);
      }
    }
    // Check for correct vertical actuation
    else if (counter_y != stepact_y)
    {
      if (abs(counter_y) > abs(stepact_y))
      {
        switch (DIR_y)
        {
          case 0:
            DIR_y = 1;
            break;
          case 1:
            DIR_y = 0;
            break;
        }
        remsteps_y = abs(counter_y - stepact_y);
      }
      else if (abs(counter_y) < abs(stepact_y))
      {
        remsteps_y = abs(counter_y - stepact_y);
      }
    }
  }
}

// Save counter_x and counter_y to EEPROM for tracking throughout flight

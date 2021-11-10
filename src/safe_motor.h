#ifndef SAFE_MOTOR_H
#define SAFE_MOTOR_H

#include "main.h"
#include "constants.h"

/*

*/

// if we would change voltage and change would be less than this, no change happens
#define MINIMUM_VOLTAGE_CHANGE 1

// used to measure which direction setting positive voltage on a motor will cause it to rotate
// forward and backward may refer to different directions in different contexts
enum MOTOR_DIRECTION {backwards=-1, forwards=1};

// same as pros::Motor, but does not change voltage unneccesarily preventing jittering
class Safe_Motor : public pros::Motor
{
public:
  // initialize and pass port to pros Motor class
  Safe_Motor(char);

  // initialize current voltage and pass port # to pros Motor class
  Safe_Motor(char, MOTOR_DIRECTION);

  // set the voltage on the motor, taking care not to change it if there would be no change
  void set_voltage(double voltage);

private:
  // stores the voltage recorded to being sent to the motor
  double current_voltage;
};

#endif

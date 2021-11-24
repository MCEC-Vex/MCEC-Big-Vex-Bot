#ifndef ARM_H
#define ARM_H

#include "main.h"
#include "safe_motor.h"

// port arm motor is connected to
#define ARM_1_PORT 1
#define ARM_2_PORT 11

// direction arm motor rotates
// forwards if positive voltage moves arm upwards
// backwards if positive voltage moves arm downwards
#define ARM_1_DIRECTION forwards
#define ARM_2_DIRECTION backwards

// voltage sent to arm motor when moving up or down
// ranges from 0 to 127
#define MOVE_VOLTAGE 60

#define ARM_STOP_VOLTAGE 60

// main arm of the bot
class Arm
{
public:

  // default constructor
  Arm();

  // --------------------------------
  // move the arm upwards or downards
  // --------------------------------

  // get input from the controller and move the arm accordingly
  void move(pros::Controller);

  // set the angle of the arm
  void set_angle(double);

private:

  // pointer to the arm motor
  Safe_Motor* arm_motor_1;
  Safe_Motor* arm_motor_2;

  double target_angle;
};

#endif

#ifndef ARM_H
#define ARM_H

#include "main.h"
#include "safe_motor.h"

// ports arm motors argument connected to
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

// voltage sent to arm motor for holding its position
// ranges from 0 to 127
#define ARM_STOP_VOLTAGE 60

// limits for how far the arm can go up and down during opcontrol
#define UPPER_ANGLE_LIMIT 90
#define LOWER_ANGLE_LIMIT 10

#define MOTOR_TO_ARM_RATIO 10

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

  // pointers to the arm motors
  Safe_Motor* arm_motor_1;
  Safe_Motor* arm_motor_2;

  // keeps track of the arm's angle
  double target_angle;
};

#endif

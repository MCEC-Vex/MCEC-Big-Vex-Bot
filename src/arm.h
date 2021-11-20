#ifndef ARM_H
#define ARM_H

#include "main.h"
#include "safe_motor.h"

// port arm motor is connected to
#define ARM_PORT 14

// direction arm motor rotates
// forwards if positive voltage moves arm upwards
// backwards if positive voltage moves arm downwards
#define ARM_DIRECTION backwards

// voltage sent to arm motor when moving up or down
// ranges from 0 to 127
#define MOVE_VOLTAGE 30

// the voltage used to keep the arm still
// high voltages will provide more force, but will create shaky stops
#define ARM_STOP_VOLTAGE 1

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

  // set the voltage of the arm to the arguemnt sent
  void move(double);

private:

  // pointer to the arm motor
  Safe_Motor* arm_motor;
};

#endif

#ifndef ARM_H
#define ARM_H

#include "main.h"
#include "safe_motor.h"

// ports arm motors argument connected to
#define ARM_1_PORT 1
#define ARM_2_PORT 11

// port for the pnuematic piston
#define PISTON_PORT 'A'

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

// math constant for
#define MOTOR_TO_ARM_RATIO 10

// Controller button for toggling the claw
#define CLAW_BUTTON pros::E_CONTROLLER_DIGITAL_A

// used to measure whether the claw is open or close
enum STATE {closed, opened};

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
  void run(pros::Controller);

  // set the angle of the arm
  void set_angle(double);

  //----------------
  // handle the claw
  // ---------------

  // open the claw
  void open();

  // close the claw
  void close();

private:

  // pointers to the arm motors
  Safe_Motor* arm_motor_1;
  Safe_Motor* arm_motor_2;

  // keeps track of the arm's angle
  double target_angle;

  // pointer to the claw's pnuematic piston
  pros::ADIDigitalOut* claw_piston;

  // tracks whether the claw is opened or closed
  STATE claw_state;
};

#endif

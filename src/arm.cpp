#include "arm.h"

// default constructor
Arm::Arm()
{
  // setup the arm motor with its port and direction
  arm_motor = new Safe_Motor(ARM_PORT, ARM_DIRECTION);
}

// --------------------------------
// move the arm upwards or downards
// --------------------------------

// get input from the controller and move the arm accordingly
void Arm::move(pros::Controller master)
{
  // if R1 is held but not R2, move arm up
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
  {
    // move arm up
    arm_motor->move(MOVE_VOLTAGE);

    // set the default position of the motor to its current position
    arm_motor->tare_position();
  }
  // if R2 is not held but R2 is, move arm down
  else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
  {
    // move arm down
    arm_motor->move(-MOVE_VOLTAGE);

    // se thte default position of hte motor to its current position
    arm_motor->tare_position();
  }
  // if R1 and R2 are held or neither are held, stop arm from moving
  else
  {
    // stop arm movement by moving setting the motor to move back to the position it was last in
    arm_motor->move_absolute(0, ARM_STOP_VOLTAGE);
  }
}

// set the voltage of the arm to the arguemnt sent
void Arm::move(double voltage)
{
  // set the voltage on the motor
  arm_motor->move(voltage);
}

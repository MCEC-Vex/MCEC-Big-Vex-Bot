#include "arm.h"

// default constructor
Arm::Arm()
{
  // setup the arm motor with its port and direction
  arm_motor_1 = new Safe_Motor(ARM_1_PORT, ARM_1_DIRECTION);
  arm_motor_2 = new Safe_Motor(ARM_2_PORT, ARM_2_DIRECTION);

  // set the brake mode on the arm motor
  arm_motor_1->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  arm_motor_2->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // set the way the arm motor measures movement internally to degrees
  arm_motor_1->set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
  arm_motor_2->set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

  // set the arm motor's zero position to its current position
  arm_motor_1->tare_position();
  arm_motor_2->tare_position();

  target_angle = 0;
}

// --------------------------------
// move the arm upwards or downards
// --------------------------------

// get input from the controller and move the arm accordingly
void Arm::move(pros::Controller master)
{
  pros::lcd::set_text(6, std::to_string(target_angle));
  // if R1 is held but not R2, move arm up
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
  {
    if (target_angle > 90)
    {
      target_angle = 90;
    }
    else
    {
      // move arm up
      arm_motor_1->move(MOVE_VOLTAGE);
      arm_motor_2->move(MOVE_VOLTAGE);
      target_angle = arm_motor_1->get_position() / 10;
    }
  }
  // if R2 is not held but R2 is, move arm down
  else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
  {
    // move arm down
    if (target_angle < 10)
    {
      target_angle = 10;
      arm_motor_1->move_absolute(10*target_angle, MOVE_VOLTAGE);
      arm_motor_2->move_absolute(10*target_angle, MOVE_VOLTAGE);
    }
    else
    {
      arm_motor_1->move(-MOVE_VOLTAGE);
      arm_motor_2->move(-MOVE_VOLTAGE);
      target_angle = arm_motor_1->get_position() / 10;
    }
  }
  // if R1 and R2 are held or neither are held, stop arm from moving
  else
  {
    // set voltage on arm motor to 0
    arm_motor_1->move_absolute(10*target_angle, ARM_STOP_VOLTAGE);
    arm_motor_2->move_absolute(10*target_angle, ARM_STOP_VOLTAGE);
  }
}

// set the voltage of the arm to the arguemnt sent
void Arm::set_angle(double angle)
{
  // set the voltage on the motor to go towards the specified angle
  arm_motor_1->move_absolute(10*angle, MOVE_VOLTAGE);
  arm_motor_2->move_absolute(10*angle, MOVE_VOLTAGE);
  target_angle = angle;
}

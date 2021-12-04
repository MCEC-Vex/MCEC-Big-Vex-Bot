#include "arm.h"

// default constructor
Arm::Arm()
{
  // setup the arm motors with their ports and directions
  arm_motor_1 = new Safe_Motor(ARM_1_PORT, ARM_1_DIRECTION);
  arm_motor_2 = new Safe_Motor(ARM_2_PORT, ARM_2_DIRECTION);

  // set the brake mode on the arm motors
  arm_motor_1->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  arm_motor_2->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // set the way the arm motors measures movement internally to degrees
  arm_motor_1->set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
  arm_motor_2->set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

  // set the arm motors' zero positions to their current position
  arm_motor_1->tare_position();
  arm_motor_2->tare_position();

  // set the angle to 0 for tracking
  target_angle = 0;

  // initialize the claw piston pointer
  claw_piston = new pros::ADIDigitalOut(PISTON_PORT);

  // open the claw
  this->open();
}

// --------------------------------
// move the arm upwards or downards
// --------------------------------

// get input from the controller and move the arm accordingly
void Arm::run(pros::Controller master)
{
  // if R1 is held but not R2, move arm up
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
  {
    // if arm is to far up, do not let it move further and keep it at max
    if (target_angle > UPPER_ANGLE_LIMIT)
    {
      // keep angle at max
      target_angle = UPPER_ANGLE_LIMIT;

      // move to max in case slightly past
      arm_motor_1->move_absolute(MOTOR_TO_ARM_RATIO*target_angle, MOVE_VOLTAGE);
      arm_motor_2->move_absolute(MOTOR_TO_ARM_RATIO*target_angle, MOVE_VOLTAGE);
    }
    // move arms up
    else
    {
      // move arms up
      arm_motor_1->move(MOVE_VOLTAGE);
      arm_motor_2->move(MOVE_VOLTAGE);

      // track angle
      target_angle = arm_motor_1->get_position() / MOTOR_TO_ARM_RATIO;
    }
  }
  // if R2 is not held but R2 is, move arm down
  else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
  {
    // if arm is too far down, do not let it move further and keep it at min
    if (target_angle < LOWER_ANGLE_LIMIT)
    {
      // keep angle at min
      target_angle = LOWER_ANGLE_LIMIT;

      // move to min in case slightly past
      arm_motor_1->move_absolute(MOTOR_TO_ARM_RATIO*target_angle, MOVE_VOLTAGE);
      arm_motor_2->move_absolute(MOTOR_TO_ARM_RATIO*target_angle, MOVE_VOLTAGE);
    }
    // move arms down
    else
    {
      // move arms down
      arm_motor_1->move(-MOVE_VOLTAGE);
      arm_motor_2->move(-MOVE_VOLTAGE);

      // track angle
      target_angle = arm_motor_1->get_position() / 10;
    }
  }
  // if R1 and R2 are held or neither are held, stop arms from moving
  else
  {
    // set voltage on arm motors to 0
    arm_motor_1->move_absolute(10*target_angle, ARM_STOP_VOLTAGE);
    arm_motor_2->move_absolute(10*target_angle, ARM_STOP_VOLTAGE);
  }

  // ---------------
  // HANDLE THE CLAW
  // ---------------

  // check if the claw's button was pressed on the controller
  if (master.get_digital_new_press(CLAW_BUTTON))
  {
    // if the claw is closed, open it now
    if (claw_state == closed)
    {
      // open the claw
      this->open();
    }
    // if the claw is opened, close it now
    else if (claw_state == opened)
    {
      // close the claw
      this->close();
    }
  }
}

// set the voltage of the arms to the arguemnt sent
void Arm::set_angle(double angle)
{
  // set the voltage on the motors to go towards the specified angle
  arm_motor_1->move_absolute(10*angle, MOVE_VOLTAGE);
  arm_motor_2->move_absolute(10*angle, MOVE_VOLTAGE);

  // track the angle
  target_angle = angle;
}

// open the claw
void Arm::open()
{
  // open the claw
  claw_piston->set_value(false);

  // set the claw's state to opened
  claw_state = opened;
}

// close the claw
void Arm::close()
{
  // close the claw
  claw_piston->set_value(true);

  // set the claw's state to closed
  claw_state = closed;
}

#include "safe_motor.h"
#include "constants.h"


Safe_Motor::Safe_Motor(char port) : pros::Motor{port}
{
  current_voltage = 0;
}

// initialize current voltage and pass port # to pros Motor class
Safe_Motor::Safe_Motor(char port, MOTOR_DIRECTION rotation_direction) : pros::Motor{port}
{
  current_voltage = 0;  // voltage of motors start at 0

  if (rotation_direction == backwards)
  {
    this->set_reversed(true);
  }
}

// set the voltage on the motor, taking care not to change it if there would be no change
// this prevents jittering
void Safe_Motor::set_voltage(double voltage)
{
  // if new voltage and old voltage are significantly different
  if (std::abs(voltage - current_voltage) > MINIMUM_VOLTAGE_CHANGE)
  {
    this->move(voltage);   // set voltage of wheel
    current_voltage = voltage;  // store new voltage for future comparisons
  }
}

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

// sets the voltage for the motor from -127 to 127 if input is different than current voltage
std::int32_t Safe_Motor::set_voltage(const std::int32_t voltage)
{
  // if new voltage and old voltage are significantly different
  if (std::abs(voltage - current_voltage) > MINIMUM_VOLTAGE_CHANGE)
  {
    return this->pros::Motor::move(voltage);   // set voltage of wheel
    current_voltage = voltage;  // store new voltage for future comparisons
  }

  return 1;
}

// sets the voltage for the motor from -127 to 127 if input is different than current voltage
std::int32_t Safe_Motor::move(const std::int32_t voltage)
{
  return this->set_voltage(voltage);
}

// Gets the actual velocity of the motor and takes into account the direction the motor is set to
double Safe_Motor::get_actual_velocity()
{
  return direction * this->pros::Motor::get_actual_velocity();
}

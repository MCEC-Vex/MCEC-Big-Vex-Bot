#include "safe_motor.h"
#include "constants.h"


Safe_Motor::Safe_Motor(std::uint8_t port) : pros::Motor{port}
{
  current_voltage = 0;
}

// initialize current voltage and pass port # to pros Motor class
Safe_Motor::Safe_Motor(std::uint8_t port, MOTOR_DIRECTION rotation_direction) : pros::Motor{port}
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
  /*
  int v = voltage;

  if (this->is_reversed())
  {
    v *= -1;
  }
  */
  // if new voltage and old voltage are significantly different
  if (std::abs(voltage - current_voltage) > MINIMUM_VOLTAGE_CHANGE)
  {
    current_voltage = voltage;  // store new voltage for future comparisons
    return this->pros::Motor::move(voltage);   // set voltage of wheel
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
  return this->pros::Motor::get_actual_velocity();
}

// set the motor position and set current_voltage correctly
std::int32_t Safe_Motor::move_absolute(double position, std::int32_t velocity)
{
  // set the movement of the motor
  std::int32_t ret_val = this->pros::Motor::move_absolute(position, velocity);

  // set the stored voltage to the current voltage we have
  current_voltage = this->get_voltage();

  // return the value given by pros::Motor::move_absolute
  return ret_val;
}

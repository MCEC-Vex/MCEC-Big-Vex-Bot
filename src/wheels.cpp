#include "main.h"
#include "wheels.h"
#include "safe_motor.h"
#include "constants.h"
#include <iostream>

Wheels::Wheels()
{
  top_left = new Safe_Motor(TOP_LEFT_WHEEL, TOP_LEFT_WHEEL_DIRECTION);
  top_right = new Safe_Motor(TOP_RIGHT_WHEEL, TOP_RIGHT_WHEEL_DIRECTION);
  bottom_left = new Safe_Motor(BOTTOM_LEFT_WHEEL, BOTTOM_LEFT_WHEEL_DIRECTION);
  bottom_right = new Safe_Motor(BOTTOM_RIGHT_WHEEL, BOTTOM_RIGHT_WHEEL_DIRECTION);

  angle = 0;
}

// set the wheel motors' voltage so that the hex bot travels in the corresponding direction at a proportional speed
// x and y range from -127 to +127
void Wheels::drive(double move_x, double move_y)
{

  // calculate the angle and the magnitude of the controller joystick
  double move_angle = std::atan2(move_y, move_x);											// theta = atan(y/x)
  double move_magnitude = std::sqrt(pow(move_x, 2) + pow(move_y, 2));	// r = sqrt(x^2 + y^2)

  // set voltage (power) to wheels
  top_left->set_voltage(move_magnitude * std::sin(move_angle + M_PI/4));        // r*sin(theta+pi/4)
  top_right->set_voltage(move_magnitude * std::sin(move_angle + 3*M_PI/4));     // r*sin(theta+3pi/4)
  bottom_left->set_voltage(move_magnitude * std::sin(move_angle - M_PI/4));     // r*sin(theta-pi/4)
  bottom_right->set_voltage(move_magnitude * std::sin(move_angle - 3*M_PI/4));  // r*sin(theta-3pi/4)
}

// drives robot while bot rotates at same time
void Wheels::drive(double move_x, double move_y, double rotation_factor)
{
  // calculate the angle and the magnitude of the controller joystick
  double move_angle = std::atan2(move_y, move_x);											// theta = atan(y/x)
  double move_magnitude = std::sqrt(pow(move_x, 2) + pow(move_y, 2));	// r = sqrt(x^2 + y^2)

  // set voltage for wheels
  // divide voltages derived for movement by 2 as half of possible voltage is allocated to rotation
  top_left->set_voltage((move_magnitude * std::sin(move_angle + M_PI/4))/2 + rotation_factor/2);        // r*sin(theta+pi/4)
  top_right->set_voltage((move_magnitude * std::sin(move_angle + 3*M_PI/4))/2 + rotation_factor/2);     // r*sin(theta+3pi/4)
  bottom_left->set_voltage((move_magnitude * std::sin(move_angle - M_PI/4))/2 + rotation_factor/2);     // r*sin(theta-pi/4)
  bottom_right->set_voltage((move_magnitude * std::sin(move_angle - 3*M_PI/4))/2 + rotation_factor/2);  // r*sin(theta-3pi/4)
}

// if drive is called with a controller argument, get vector of motion from controller instead
void Wheels::drive(pros::Controller master)
{
  // if controller right joystick x has a significant value, we are rotating as well
  if (abs(master.get_analog(ROTATION_ANALOG)) > 5)
  {
    // pass in left joystick x and y as movement vector and right joystick x as rotation factor
    drive(master.get_analog(X_MOVE_ANALOG),
                            master.get_analog(Y_MOVE_ANALOG),
                            master.get_analog(ROTATION_ANALOG));
  } else {
    // pass in the x and y components of the left joystick as move_x and move_y in drive()
    drive(master.get_analog(X_MOVE_ANALOG),
          master.get_analog(Y_MOVE_ANALOG));
  }

}

// set the wheel motors' voltage so that the hex bot rotates in place in the corresponding direction at a proportional speed
// rotation_factor ranges from -127 to +127 where -127 is max speed CCW and +127 is max speed CW
void Wheels::rotate(double rotation_factor)
{
  // ensure the voltage of each wheel is the rotation factor
  top_left->set_voltage(rotation_factor);
  top_right->set_voltage(rotation_factor);
  bottom_left->set_voltage(rotation_factor);
  bottom_right->set_voltage(rotation_factor);
}

// if rotate is called with a controller argument, get rotation speed and direction from controller instead
void Wheels::rotate(pros::Controller master)
{
  rotate(master.get_analog(ROTATION_ANALOG));  // get the x of the left joystick and pass that as the rotation_factor
}

void Wheels::stop()
{
  top_left->set_voltage(0);
  top_right->set_voltage(0);
  bottom_left->set_voltage(0);
  bottom_right->set_voltage(0);
}

void Wheels::output_temperatures()
{
  pros::lcd::set_text(1, "Top Left Temperature: " + std::to_string(top_left->get_temperature()));
  pros::lcd::set_text(2, "Top Right Temperature: " + std::to_string(top_right->get_temperature()));
  pros::lcd::set_text(3, "Bottom Left Temperature: " + std::to_string(bottom_left->get_temperature()));
  pros::lcd::set_text(4, "Bottom Right Temperature: " + std::to_string(bottom_right->get_temperature()));
}

void Wheels::run()
{

    //TOP_LEFT_WHEEL_DIRECTION * 0.001 * TICK_DELAY * top_left->get_actual_velocity() * (60 / (WHEEL_DIAMETER*M_PI));
    double top_left_velocity = TOP_LEFT_WHEEL_DIRECTION * top_left->get_actual_velocity();
    double top_right_velocity = TOP_RIGHT_WHEEL_DIRECTION * top_left->get_actual_velocity();
    double bottom_left_velocity = BOTTOM_LEFT_WHEEL_DIRECTION * top_left->get_actual_velocity();
    double bottom_right_velocity = BOTTOM_RIGHT_WHEEL_DIRECTION * top_left->get_actual_velocity();

    //double left_delta_y = (M_PI*WHEEL_DIAMETER*TICK_DELAY/120000)*(top_left_velocity + bottom_left_velocity);
    //double right_delta_y = (M_PI*WHEEL_DIAMETER*TICK_DELAY/120000)*(top_right_velocity + bottom_right_velocity);
    double left_delta_y = (M_PI*WHEEL_DIAMETER*TICK_DELAY*0.001*std::sqrt(2)/120)*(top_left_velocity + bottom_left_velocity);
    double right_delta_y = (M_PI*WHEEL_DIAMETER*TICK_DELAY*0.001*std::sqrt(2)/120)*(top_right_velocity + bottom_right_velocity);
    //double left_delta_y = (top_left_position_change + bottom_left_position_change) * std::sin(M_PI/4);
    //double right_delta_y = (-top_right_position_change + -bottom_right_position_change) * std::sin(M_PI/4);

    double angle_change = (left_delta_y - right_delta_y) / (DISTANCE_BETWEEN_WHEELS);

    angle += angle_change;

    pros::lcd::set_text(3, std::to_string(angle));
    //std::cout << angle << std::endl;
    //std::cout << "(" << left_delta_y << " - " << right_delta_y << ") / 32 = " << angle_change << std::endl;
}

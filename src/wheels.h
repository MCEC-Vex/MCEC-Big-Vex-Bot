#ifndef WHEELS_H
#define WHEELS_H

#include "main.h"
#include "safe_motor.h"

// ports for the wheels
#define TOP_LEFT_WHEEL 15
#define TOP_RIGHT_WHEEL 4
#define BOTTOM_LEFT_WHEEL 16
#define BOTTOM_RIGHT_WHEEL 10

// directions of the wheels
// forwards would cause the bot to rotate clockwase if all motors have +127 voltage
#define TOP_LEFT_WHEEL_DIRECTION backwards
#define TOP_RIGHT_WHEEL_DIRECTION backwards
#define BOTTOM_LEFT_WHEEL_DIRECTION backwards
#define BOTTOM_RIGHT_WHEEL_DIRECTION backwards

// controller analogs that control certain wheel methods
#define X_MOVE_ANALOG pros::E_CONTROLLER_ANALOG_LEFT_X
#define Y_MOVE_ANALOG pros::E_CONTROLLER_ANALOG_LEFT_Y
#define ROTATION_ANALOG pros::E_CONTROLLER_ANALOG_RIGHT_X

// physical properties of wheel system
#define WHEEL_DIAMETER 3.3
#define DISTANCE_BETWEEN_WHEELS 14.81

// keeps track of the 4 wheels
class Wheels
{
public:
	Wheels();	// default constructor

	// set the wheel motors' voltage so that the hex bot travels in the corresponding direction at a proportional speed
	// given the vector of motion for the robot
	void drive(double, double);

	// drives robot while bot rotates at same time
	void drive(double, double, double);

	// if drive is called with a controller argument, get vector of motion from controller instead
	void drive(pros::Controller);

	// set the wheel motors' voltage so that the hex bot rotates in place in the corresponding direction at a proportional speed
	// given the direction and speed of rotation
	void rotate(double);

	// if rotate is called with a controller argument, get rotation speed and direction from controller instead
	void rotate(pros::Controller);

	// stop all wheel motors
	void stop();

	// print wheel motor temperatures to lcd screen
	void output_temperatures();

	// handle instructions that should be run every frame to keep wheel's information up to date
	void run();

<<<<<<< Updated upstream
	// angle getter and setter
	double get_angle() const;
	void set_angle(double);
	
=======
	// angle getter
	double get_angle() const;

	// angle setter
	void set_angle(double);

>>>>>>> Stashed changes
private:
	// pointers to wheel motors
	Safe_Motor* top_left;			// points to top_left wheel motor
	Safe_Motor* top_right;			// points to top_right wheel motor
	Safe_Motor* bottom_left;		// points to bottom_left wheel motor
	Safe_Motor* bottom_right;	// points to bottom_right wheel motor

	double angle;				// angle of the robot (in radians)

	// (rounds / minute) * (pi d inches / 1 round) * (1 minute / 60 seconds) * (milliseconds per tick / 1 millisecond)
	const double rpm_to_inches_per_tick = M_PI * WHEEL_DIAMETER / 60 / 1000 * TICK_DELAY;
};

#endif

#ifndef GRABBER_H
#define GRABBER_H

#include "main.h"
#include "safe_motor.h"
#include <ctime>

// motor port
#define GRABBER_MOTOR 10

// controller buttons for controlling grabber
#define OPENING_BUTTON pros::E_CONTROLLER_DIGITAL_R1
#define CLOSING_BUTTON pros::E_CONTROLLER_DIGITAL_R2

#define GRABBER_MOTOR_DIRECTION forwards

// voltage when operating grabber
#define OPENING_VOLTAGE -50
#define CLOSING_VOLTAGE 100

// duration grabber takes to open
#define OPENING_DURATION 1

// different states of grabber
enum state {INACTIVE, OPENING, CLOSING};

// class for the grabber motor
class Grabber
{
public:
  Grabber();    // default constructor
  void open();  // open the grabber
  void close(); // close grabber and hold it closed

  // any run method should be run once per frame. The Motor might not stop at the correct time
  void run(pros::Controller); // run Grabber instructions, getting instructions from controller
  void run();                 // run Grabber instructions
private:
  Safe_Motor* grab_motor;     // pointer to the motor controlling the Grabber

  state grabber_state;        // current state of the grabber's motor

  time_t movement_start;      // the time at which motor started moving
};

#endif

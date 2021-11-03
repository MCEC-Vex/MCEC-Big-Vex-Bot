#include "grabber.h"
#include <ctime>

// default constructor
Grabber::Grabber()
{
  grab_motor = new Safe_Motor(GRABBER_MOTOR, GRABBER_MOTOR_DIRECTION); // create a motor object

  // starting state of Grabber motor is inactive
  grabber_state = INACTIVE;
}

// open the Grabber
void Grabber::open()
{
  // if grabber is already opening, stop opening if enough time has passed
  if (grabber_state == OPENING)
  {
    // compare the current time with the time when the motor started moving.
    if (time(0) - movement_start > OPENING_DURATION)
    {
      // stop motor
      grab_motor->set_voltage(0);

      // set grabber to inactive
      grabber_state = INACTIVE;
    }
  } else {  // begin opening the grabber
    // set grabber to opening
    grabber_state = OPENING;

    // set voltage of grabber motor
    grab_motor->set_voltage(OPENING_VOLTAGE);

    // record the current time
    movement_start = time(0);
  }
}

// close grabber and hold it closed
void Grabber::close()
{
  // set grabber to closing
  grabber_state = CLOSING;

// set voltage of grabber motor
  grab_motor->set_voltage(CLOSING_VOLTAGE);
}

// run Grabber instructions, getting instructions from controller
void Grabber::run(pros::Controller master)
{
  // if opening buttor is hit, open grabber
  if (master.get_digital_new_press(OPENING_BUTTON))
  {
    open(); // open grabber
  } else if (master.get_digital_new_press(CLOSING_BUTTON)) {  // if closing button is hit, close grabber
    close();  // close grabber
  }

  run();  // run additional instruction required to keep track of timers
}

// run Grabber instructions
// specifically instructions that keep track of or utilize timers
void Grabber::run()
{
  // if the grabber is opening, continue opening the grabber
  if (grabber_state == OPENING)
  {
    open(); // open grabber
  }
}

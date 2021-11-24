#ifndef CLAW_H
#define CLAW_H

#include "main.h"

// port for the pnuematic piston
#define PISTON_PORT 'A'

#define CLAW_BUTTON pros::E_CONTROLLER_DIGITAL_A

// used to measure whether the claw is open or close
enum STATE {closed, opened};

// class controlling the robot's claw
class Claw
{
public:

  // default constructor
  Claw();

  // open the claw
  void open();

  // close the claw
  void close();

  // open or close the claw based on controller input
  void run(pros::Controller);

private:

  // pointer to the claw's pnuematic piston
  pros::ADIDigitalOut* piston;

  // tracks whether the claw is opened or closed
  STATE claw_state;

};

#endif

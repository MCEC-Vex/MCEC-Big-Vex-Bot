#include "main.h"
#include "claw.h"

// default constructor
Claw::Claw()
{
  // initialize the piston pointer
  piston = new pros::ADIDigitalOut(PISTON_PORT);

  // open the claw
  this->open();
}

// open the claw
void Claw::open()
{
  // open the claw
  piston->set_value(true);

  // set the claw's state to opened
  claw_state = opened;
}

// close the claw
void Claw::close()
{
  // close the claw
  piston->set_value(false);

  // set the claw's state to closed
  claw_state = closed;
}

// open or close the claw based on controller input
void Claw::run(pros::Controller master)
{
  // check if "A" was pressed on the controller
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
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

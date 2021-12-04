#ifndef AUTO_H
#define AUTO_H

#include "main.h"
#include "wheels.h"

// WIP
#define FIND_GOAL_ROTATION_VOLT 20
#define SWEEP_ANGLE 60
bool find_goal(Wheels* holo_drive)
{
  holo_drive->rotate(FIND_GOAL_ROTATION_VOLT);
  holo_drive->set_angle(0);

  while(std::abs(holo_drive->get_angle()) < SWEEP_ANGLE*M_PI/180)
  {
    if (false) // placeholder. check if goal in front
    {

    }
  }

  return true;
}

#endif

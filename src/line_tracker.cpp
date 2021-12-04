#include "main.h"
#include "line_tracker.h"

Line_Tracker::Line_Tracker()
{
  sensor = new pros::ADIAnalogIn(SENSOR_PORT);

  cross_count = -1;

  state = dark;
}

bool Line_Tracker::is_pale() const
{
  if (sensor->get_value() < PALE_THRESHOLD)
  {
    return true;
  }

  return false;
}

void Line_Tracker::run()
{
  if (this->is_pale() && state == dark)
  {
    state = pale;
    cross_count++;
  }
  else if (!this->is_pale() && state == pale)
  {
    state = dark;
  }
}

int Line_Tracker::get_cross_count() const
{
  return cross_count;
}

void Line_Tracker::set_cross_count(int new_count)
{
  cross_count = new_count;
}

void Line_Tracker::reset_cross_count()
{
  this->set_cross_count(0);
}

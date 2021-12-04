#ifndef LINE_TRACKER_H
#define LINE_TRACKER_H

#include "main.h"

#define SENSOR_PORT 'H'

#define PALE_THRESHOLD 1500

enum PALE_STATE {dark, pale};

class Line_Tracker
{
public:

  Line_Tracker();

  bool is_pale() const;

  void run();

  int get_cross_count() const;

  void set_cross_count(int);

  void reset_cross_count();

private:

  pros::ADIAnalogIn* sensor;

  int cross_count;

  PALE_STATE state;

};

#endif

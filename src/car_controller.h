#ifndef CAR_CONTROLLER
#define CAR_CONTROLLER

#include "car.h"

class CarController
{
public:
  void accelerate();
  void reverse();
  void release();
  void turn_left();
  void turn_right();
  void stop_turn();

  float get_x();
  float get_y();
  float get_rot();
  float get_velocity();

  void set_car(Car *car);

private:
  Car *car;
};

#endif /* CAR_CONTROLLER */

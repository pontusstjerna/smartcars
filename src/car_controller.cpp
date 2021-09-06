#include "car_controller.h"

void CarController::accelerate()
{
  car->accelerate();
}
void CarController::reverse()
{
  car->reverse();
}
void CarController::release()
{
  car->stop();
}
void CarController::turn_left()
{
  car->turn_left();
}
void CarController::turn_right()
{
  car->turn_right();
}
void CarController::stop_turn()
{
  car->stop_turn();
}

float CarController::get_x()
{
  return car->get_x();
}
float CarController::get_y()
{
  return car->get_y();
}
float CarController::get_rot()
{
  return car->get_rot();
}
float CarController::get_velocity()
{
  return car->get_velocity();
}

void CarController::set_car(Car *car)
{
  this->car = car;
}

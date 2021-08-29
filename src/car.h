#ifndef CAR_H
#define CAR_H

#include "phys_object.h"
#include "body_data.h"

#include <box2d/box2d.h>

class Car : PhysObject
{
public:
  Car(b2World *phys_world, float x, float y, float rot);
  ~Car();

  // 1.95 meter wide, 2 meters long
  const float width = 1.95;
  const float length = 2;

  void update(float d_time);

  float get_x();
  float get_y();
  float get_rot();

  void accelerate();
  void reverse();
  void stop();
  void turn_left();
  void turn_right();
  void stop_turn();

private:
  // acc = m/s^2
  // vel = m/s
  // ang_vel = rad/s
  const float max_acceleration = 20.0f;
  const float engine_brake_acceleration = 10.0f;
  const float max_speed = 8.3f;
  const float min_reverse_speed = -3.0f;
  const float max_angular_velocity = 1.50f;
  const float min_turn_velocity = 1.0f;

  float velocity = 0.0f;
  float acceleration = 0.0f;
  float angular_velocity = 0.0f;

  b2Body *body;
};

#endif /* CAR */

#ifndef CAR_H
#define CAR_H

#include "phys_object.h"
#include "dynamic_body.h"
#include "body_data.h"

#include <box2d/box2d.h>

class Car : public DynamicBody, public PhysObject
{
public:
  Car(float x, float y, float rot, b2World *phys_world, int index);

  // 1.95 meter wide, 2 meters long
  static constexpr float WIDTH = 1.95;
  static constexpr float LENGTH = 2;

  void update(float d_time);

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
};

#endif /* CAR */

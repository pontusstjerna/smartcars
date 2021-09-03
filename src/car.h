#ifndef CAR_H
#define CAR_H

#include "dynamic_body.h"
#include "body_data.h"
#include "wheel.h"
#include "point.h"

#include <box2d/box2d.h>
#include <vector>

class Car : public DynamicBody
{
public:
  enum WheelPos
  {
    FRONT_LEFT,
    FRONT_RIGHT,
    REAR_RIGHT,
    REAR_LEFT
  };

  Car(float x, float y, float rot, b2World *phys_world, int index);
  ~Car();

  // 1.2 meter wide, 2 meters long
  static constexpr float WIDTH = 1.2;
  static constexpr float LENGTH = 2;

  // Offsets are in pixels times pixel => meter ratio
  // The points are from car center to wheel center
  const std::vector<Point> wheel_offsets =
      {Point(-0.33f * 2.5f, 0.26f * 2.5f),
       Point(0.33f * 2.5f, 0.26f * 2.5f),
       Point(0.33f * 2.5f, -0.2f * 2.5f),
       Point(-0.33f * 2.5f, -0.2f * 2.5f)};

  void update(float d_time);

  void accelerate();
  void reverse();
  void stop();
  void turn_left();
  void turn_right();
  void stop_turn();

  std::vector<Wheel *> get_wheels();

private:
  // acc = m/s^2
  // vel = m/s
  // ang_vel = rad/s
  const float max_acceleration = 20.0f;
  const float min_reverse_acceleration = -3.0f;
  const float max_angular_velocity = 1.50f;
  const float min_turn_velocity = 1.0f;

  float velocity = 0.0f;
  float acceleration = 0.0f;
  float angular_velocity = 0.0f;

  std::vector<Wheel *> wheels = std::vector<Wheel *>(4, NULL);
  std::vector<b2RevoluteJoint *> front_wheel_joints;

  void kill_orthogonal_velocity(b2Body *target);
};

#endif /* CAR */

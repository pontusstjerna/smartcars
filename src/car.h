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

  Car(Point start, float rot, b2World *phys_world, int index);
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
  const float ANGULAR_DAMPING = 1;
  const float LINEAR_DAMPING = 2.5f;
  const float MAX_ACCELERATION = 20.0f;
  const float MIN_REVERSE_ACCELERATION = -10.0f;
  const float STEER_SPEED = 2.0f;        // radians per second
  const float MAX_STEERING_ANGLE = 0.5f; // radians
  const float SKID_AMOUNT = 0.3f;        // how much of orthogonal velocity to keep

  float acceleration = 0.0f;
  float target_steering_angle = 0;

  std::vector<Wheel *> wheels = std::vector<Wheel *>(4, NULL);
  std::vector<b2RevoluteJoint *> front_wheel_joints;

  void reduce_orthogonal_velocity(b2Body *target);
};

#endif /* CAR */

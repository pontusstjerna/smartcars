#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iostream>

#include "car.h"
#include "body_data.h"

using namespace std;

Car::Car(
    float x,
    float y,
    float rot,
    b2World *phys_world,
    int index) : DynamicBody(x, y, WIDTH, LENGTH, rot, phys_world, BodyData(BodyType::CAR, index))
{
  b2PolygonShape dynamic_box;
  dynamic_box.SetAsBox(WIDTH / 2.0f, LENGTH / 2.0f);

  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = 1.0f;
  fixture_def.friction = 0.1f;

  body->CreateFixture(&fixture_def);

  for (int i = 0; i < wheel_offsets.size(); i++)
  {
    Wheel *wheel = new Wheel(x + wheel_offsets[i].x, y + wheel_offsets[i].y, rot, phys_world);
    wheels[i] = wheel;

    if (i == WheelPos::FRONT_LEFT || i == WheelPos::FRONT_RIGHT)
    {
      b2RevoluteJointDef joint_def;
      b2Body *front_wheel_body = wheel->get_body();
      joint_def.Initialize(body, front_wheel_body, front_wheel_body->GetWorldCenter());

      // Turning motor
      joint_def.enableMotor = true;
      joint_def.maxMotorTorque = 100;

      b2RevoluteJoint *joint = (b2RevoluteJoint *)phys_world->CreateJoint(&joint_def);
      front_wheel_joints.push_back(joint);
    }
    else
    {
      b2PrismaticJointDef joint_def;
      b2Body *rear_wheel_body = wheel->get_body();
      joint_def.Initialize(body, rear_wheel_body, rear_wheel_body->GetWorldCenter(), b2Vec2(1, 0));
      joint_def.enableLimit = true;
      joint_def.lowerTranslation = 0;
      joint_def.upperTranslation = 0;

      phys_world->CreateJoint(&joint_def);
    }
  }
}

Car::~Car()
{
  for (Wheel *wheel : wheels)
  {
    delete wheel;
  }
}

void Car::update(float d_time)
{
  float new_velocity = velocity + acceleration * d_time;

  // Deaccelerate to 0
  if (acceleration == engine_brake_acceleration)
  {
    velocity = min(0.0f, new_velocity);
  }
  else if (acceleration == -engine_brake_acceleration)
  {
    velocity = max(0.0f, new_velocity);
  }
  else
  {
    velocity = max(min_reverse_speed, min(max_speed, new_velocity));
  }

  float angle = body->GetAngle();
  body->SetLinearVelocity(b2Vec2(velocity * sin(angle), velocity * cos(angle)));

  for (auto joint : front_wheel_joints)
  {
    joint->SetMotorSpeed(angular_velocity);
  }
}

void Car::accelerate()
{
  acceleration = max_acceleration;
}

void Car::stop()
{
  acceleration = velocity > 0 ? -engine_brake_acceleration : engine_brake_acceleration;
}

void Car::reverse()
{
  acceleration = -max_acceleration;
}

void Car::turn_left()
{
  angular_velocity = -max_angular_velocity;
}

void Car::turn_right()
{
  angular_velocity = max_angular_velocity;
}

void Car::stop_turn()
{
  angular_velocity = 0.0f;
}

vector<Wheel *> Car::get_wheels()
{
  return wheels;
}

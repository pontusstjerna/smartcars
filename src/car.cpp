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
  fixture_def.friction = 10.0f;

  body->CreateFixture(&fixture_def);
  body->SetAngularDamping(100);
  body->SetLinearDamping(1);

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

  for (int i = 0; i < wheels.size(); i++)
  {
    Wheel *wheel = wheels[i];
    kill_orthogonal_velocity(wheel->get_body());

    if (i == WheelPos::FRONT_LEFT || i == WheelPos::FRONT_RIGHT)
    {
      b2Body *wheel_body = wheel->get_body();
      float angle = wheel_body->GetAngle();

      b2Vec2 force = b2Vec2(acceleration * -sin(angle), acceleration * cos(angle));
      wheel_body->ApplyForce(force, wheel_body->GetPosition(), true);
    }
  }

  for (auto joint : front_wheel_joints)
  {
    float d_angle = target_steering_angle - joint->GetJointAngle();
    joint->SetMotorSpeed(d_angle * steer_speed);
  }
}

void Car::accelerate()
{
  acceleration = max_acceleration;
}

void Car::stop()
{
  acceleration = 0;
}

void Car::reverse()
{
  acceleration = min_reverse_acceleration;
}

void Car::turn_left()
{
  target_steering_angle = max_steering_angle;
}

void Car::turn_right()
{
  target_steering_angle = -max_steering_angle;
}

void Car::stop_turn()
{
  target_steering_angle = 0;
}

vector<Wheel *> Car::get_wheels()
{
  return wheels;
}

// vinkelrät för fan
void Car::kill_orthogonal_velocity(b2Body *target)
{
  b2Vec2 velocity = target->GetLinearVelocityFromLocalPoint(b2Vec2(0, 0));

  float angle = target->GetAngle();
  b2Vec2 orthogonal_axis = b2Vec2(-sin(angle), cos(angle));

  // The dot product tells us how much of velocity is projected on orthogonal axis
  float orthogonal_velocity_mag = b2Dot(velocity, orthogonal_axis);
  b2Vec2 orthogonal_velocity = b2Vec2(orthogonal_axis.x * orthogonal_velocity_mag, orthogonal_axis.y * orthogonal_velocity_mag);

  target->SetLinearVelocity(orthogonal_velocity);
}

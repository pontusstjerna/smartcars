#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iostream>

#include "car.h"

using namespace std;

Car::Car(b2World *phys_world, float x, float y, float rot)
{
  // TODO: Create body with x, y and rot
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(x, y);

  body = phys_world->CreateBody(&bodyDef);

  b2PolygonShape dynamic_box;
  // TODO: Add width + height
  dynamic_box.SetAsBox(width / 2.0f, length / 2.0f);

  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = 1.0f;
  fixture_def.friction = 0.1f;

  body->CreateFixture(&fixture_def);
}

Car::~Car()
{
  body = NULL;
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
  // Swap y-coordinates (in SDL y-axis is flipped in comparison to box2d)
  body->SetLinearVelocity(b2Vec2(velocity * sin(angle), -velocity * cos(angle)));

  if (abs(velocity) > min_turn_velocity)
  {
    body->SetAngularVelocity(velocity > 0 ? angular_velocity : -angular_velocity);
  }
  else if (abs(body->GetAngularVelocity()) > min_turn_velocity)
  {
    body->SetAngularVelocity(0);
  }
}

float Car::get_x()
{
  return body->GetPosition().x;
}

float Car::get_y()
{
  return body->GetPosition().y;
}

float Car::get_rot()
{
  return body->GetAngle() * (180 / M_PI);
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

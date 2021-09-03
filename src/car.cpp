#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iostream>

#include "car.h"
#include "body_data.h"
/*
TODO: Real car physics. 
https://www.emanueleferonato.com/2009/04/06/two-ways-to-make-box2d-cars/

*/

using namespace std;

Car::Car(
    float x,
    float y,
    float rot,
    b2World *phys_world,
    int index) : DynamicBody(x, y, rot, phys_world), PhysObject(BodyData(BodyType::CAR, index))
{
  b2PolygonShape dynamic_box;
  // TODO: Add width + height
  dynamic_box.SetAsBox(WIDTH / 2.0f, LENGTH / 2.0f);

  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = 1.0f;
  fixture_def.friction = 0.1f;

  body->CreateFixture(&fixture_def);
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

  if (abs(velocity) > min_turn_velocity)
  {
    body->SetAngularVelocity(velocity > 0 ? angular_velocity : -angular_velocity);
  }
  else if (abs(body->GetAngularVelocity()) > min_turn_velocity)
  {
    body->SetAngularVelocity(0);
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

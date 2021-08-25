#define _USE_MATH_DEFINES
#include <math.h>

#include "car.h"

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

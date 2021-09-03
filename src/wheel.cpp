#define _USE_MATH_DEFINES
#include <math.h>

#include "wheel.h"

Wheel::Wheel(float x,
             float y,
             float rot,
             b2World *phys_world)
    : DynamicBody(x,
                  y,
                  WIDTH,
                  LENGTH,
                  rot,
                  phys_world,
                  BodyData(BodyType::WHEEL))
{
  b2PolygonShape dynamic_box;
  dynamic_box.SetAsBox(WIDTH / 2.0f, LENGTH / 2.0f);

  b2FixtureDef fixture_def;
  fixture_def.shape = &dynamic_box;
  fixture_def.density = 1.0f;
  fixture_def.friction = 0.1f;

  body->CreateFixture(&fixture_def);
}

b2Body *Wheel::get_body()
{
  return body;
}

#define _USE_MATH_DEFINES
#include <math.h>

#include "dynamic_body.h"

DynamicBody::DynamicBody(float x,
                         float y,
                         float width,
                         float length,
                         float rot,
                         b2World *phys_world,
                         BodyData body_data) : width(width), length(length), PhysObject(body_data)
{
  // TODO: Create body with x, y and rot
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(x, y);
  bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

  body = phys_world->CreateBody(&bodyDef);
}

DynamicBody::~DynamicBody()
{
  body = NULL;
}

float DynamicBody::get_x()
{
  return body->GetPosition().x;
}

float DynamicBody::get_y()
{
  return body->GetPosition().y;
}

float DynamicBody::get_rot()
{
  return body->GetAngle() * (180 / M_PI);
}

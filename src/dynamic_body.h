#ifndef DYNAMIC_BODY
#define DYNAMIC_BODY

#include "phys_object.h"

#include <box2d/box2d.h>

class DynamicBody : public PhysObject
{
public:
  DynamicBody(
      float x,
      float y,
      float width,
      float length,
      float rot,
      b2World *phys_world,
      BodyData body_data);
  ~DynamicBody();

  const float width, length;

  float get_x();
  float get_y();
  float get_rot();
  float get_velocity();

protected:
  b2Body *body;
};

#endif /* DYNAMIC_BODY */

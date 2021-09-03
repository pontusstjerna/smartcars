#ifndef DYNAMIC_BODY
#define DYNAMIC_BODY

#include <box2d/box2d.h>

class DynamicBody
{
public:
  DynamicBody(float x, float y, float rot, b2World *phys_world);
  ~DynamicBody();

  float get_x();
  float get_y();
  float get_rot();

protected:
  b2Body *body;
};

#endif /* DYNAMIC_BODY */

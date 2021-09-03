#ifndef WHEEL_H
#define WHEEL_H

#include "phys_object.h"

#include <box2d/box2d.h>

class Wheel : PhysObject
{
public:
  static constexpr float WIDTH = 0.2f;
  static constexpr float HEIGHT = 0.5f;

  Wheel(float x, float y, float rot);

  float get_x();
  float get_y();
  float get_rot();

private:
  b2Body *body;
};

#endif /* WHEEL */

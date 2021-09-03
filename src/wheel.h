#ifndef WHEEL_H
#define WHEEL_H

#include "phys_object.h"
#include "dynamic_body.h"

#include <box2d/box2d.h>

class Wheel : public DynamicBody, public PhysObject
{
public:
  // 2.5 is the pixel to meter ratio
  static constexpr float WIDTH = 0.21f * 2.5f;
  static constexpr float LENGTH = 0.16f * 2.5f;

  Wheel(float x, float y, float rot, b2World *phys_world);

  float get_x();
  float get_y();
  float get_rot();
};

#endif /* WHEEL */

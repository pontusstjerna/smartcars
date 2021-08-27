#ifndef POINT
#define POINT

#include <box2d/box2d.h>

struct Point
{
  float x, y;

  Point() {}
  Point(float x, float y) : x(x), y(y) {}

  b2Vec2 to_b2Vec2()
  {
    return b2Vec2(x, y);
  }

  Point add(float x, float y)
  {
    return Point(this->x + x, this->y + y);
  }
};

#endif /* POINT */

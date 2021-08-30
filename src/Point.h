#ifndef POINT
#define POINT

#include <box2d/box2d.h>
#include <math.h>

struct Point
{
  float x, y;

  Point() {}
  Point(float x, float y) : x(x), y(y) {}

  b2Vec2 to_b2Vec2() const
  {
    return b2Vec2(x, y);
  }

  Point add(float x, float y) const
  {
    return Point(this->x + x, this->y + y);
  }

  Point add(Point other)
  {
    return add(other.x, other.y);
  }

  // Where 0 rad is straight north, PI / 2 is straight east etc
  float get_heading(Point other) const
  {
    return atan2(other.x - x, other.y - y);
  }
};

#endif /* POINT */

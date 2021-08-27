#ifndef GOAL_LINE
#define GOAL_LINE

#include "Point.h"

#include <box2d/box2d.h>

class GoalLine
{
public:
  GoalLine(Point start, Point end, b2World *phys_world);

  const Point start;
  const Point end;
};

#endif /* GOAL_LINE */

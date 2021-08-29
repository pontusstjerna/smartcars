#ifndef GOAL_LINE_H
#define GOAL_LINE_H

#include "point.h"
#include "phys_object.h"

#include <box2d/box2d.h>

class GoalLine : public PhysObject
{
public:
  GoalLine(Point start, Point end, b2World *phys_world);

  const Point start;
  const Point end;
};

#endif /* GOAL_LINE_H */

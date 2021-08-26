#ifndef TRACK_SEGMENT
#define TRACK_SEGMENT

#include "Point.h"

#include <vector>
#include <box2d/box2d.h>

class TrackSegment
{
public:
  TrackSegment(std::vector<Point>, b2World *phys_world, Point prev_ghost, Point next_ghost);

  std::vector<Point> get_points();

  const float width = 1;

private:
  std::vector<Point> points;
};

#endif /* TRACK_SEGMENT */

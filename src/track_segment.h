#ifndef TRACK_SEGMENT_H
#define TRACK_SEGMENT_H

#include "Point.h"
#include "phys_object.h"

#include <vector>
#include <box2d/box2d.h>

class TrackSegment : public PhysObject
{
public:
  // For standalone segments
  TrackSegment(std::vector<Point>, b2World *phys_world, Point prev_ghost, Point next_ghost);

  // For loop segments
  TrackSegment(std::vector<Point>, b2World *phys_world);

  std::vector<Point> get_points();

  const float width = 1;

private:
  std::vector<Point> points;

  void create_segment(b2ChainShape *chain_shape, b2World *phys_world);
  void create_vertices(b2Vec2 *arr, std::vector<Point> points);
};

#endif /* TRACK_SEGMENT */

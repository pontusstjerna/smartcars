#include "track.h"

Track::Track(string name, b2World *phys_world) : width(40), height(30)
{
  segments = create_track(name, phys_world);
}

Track::Track(b2World *phys_world) : Track("default", phys_world) {}

vector<TrackSegment> Track::get_segments()
{
  return segments;
}

vector<TrackSegment> Track::create_track(string name, b2World *phys_world)
{
  if (name == "default")
  {
    vector<Point> outer_points = {
        Point(1, 1),
        Point(1, height - 1),
        Point(width - 1, height - 1),
        Point(width - 1, height / 2),
        Point(15, height / 2),
        Point(15, (height / 2) - 1),
        Point(width - 1, (height / 2) - 1),
        Point(width - 1, 1),
        Point(1, 1)};
    TrackSegment segment = TrackSegment(outer_points, phys_world);
    return vector<TrackSegment>{segment};
  }
}
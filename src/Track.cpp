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
    vector<Point> points = {
        Point(5, height - 5),
        Point(4 * width / 5, height - 5),
        Point(4 * width / 5, height / 3),
        Point(width / 2, height / 3),
        Point(5, 8)};
    TrackSegment segment = TrackSegment(
        points,
        phys_world,
        Point(0, height - 5),
        Point(5, 5));
    return {segment};
  }
}
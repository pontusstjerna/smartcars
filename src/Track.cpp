#include "track.h"

#include <math.h>

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
  float track_width = 5;

  if (name == "default")
  {
    vector<Point> outer_points = {
        Point(1, 1),
        Point(1, height - 1),
        Point(width - 1, height - 1),
        Point(width - 1, height / 2 + 1),
        Point(15, height / 2 + 1),
        Point(15, (height / 2) - 1),
        Point(width - 1, (height / 2) - 1),
        Point(width - 1, 1),
        Point(1, 1)};

    vector<Point> inner_points = create_inner_points(outer_points);

    return vector<TrackSegment>{
        TrackSegment(outer_points, phys_world),
        TrackSegment(inner_points, phys_world)};
  }
}

// This is a test for the future when auto-generating tracks
vector<Point> Track::create_inner_points(vector<Point> outer_points)
{
  float track_width = 6;

  vector<Point> inner_points;
  for (int i = 0; i < outer_points.size(); i++)
  {
    Point prev_outer = i > 0 ? outer_points[i - 1] : outer_points[outer_points.size() - 2];
    Point outer = outer_points[i];
    Point next_outer = i < outer_points.size() - 1 ? outer_points[i + 1] : outer_points[0];

    float next_heading = atan2(next_outer.x - outer.x, next_outer.y - outer.y);
    float prev_heading = atan2(outer.x - prev_outer.x, outer.y - prev_outer.y);

    // This formula is written in bug blood
    inner_points.insert(
        inner_points.begin(),
        outer.add(
            track_width * cos(next_heading) + track_width * cos(prev_heading),
            track_width * -sin(next_heading) + track_width * -sin(prev_heading)));
  }

  return inner_points;
}
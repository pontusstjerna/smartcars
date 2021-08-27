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
  float track_width = 6;

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

    vector<Point> inner_points = {
        outer_points[8].add(track_width, track_width),
        outer_points[7].add(-track_width, track_width),
        outer_points[6].add(-track_width, -track_width),
        outer_points[5].add(-track_width, -track_width),
        outer_points[4].add(-track_width, track_width),
        outer_points[3].add(-track_width, track_width),
        outer_points[2].add(-track_width, -track_width),
        outer_points[1].add(track_width, -track_width),
        outer_points[0].add(track_width, track_width)};

    return vector<TrackSegment>{
        TrackSegment(outer_points, phys_world),
        TrackSegment(inner_points, phys_world)};
  }
}

// This is a test for the future when auto-generating tracks
vector<Point> create_inner_points(vector<Point> outer_points)
{
  float width = 10;

  vector<Point> inner_points;
  for (int i = 1; i < outer_points.size() - 1; i++)
  {
    Point prev_outer = outer_points[i - 1];
    Point outer = outer_points[i];
    Point next_outer = outer_points[i + 1];

    float outer_heading = atan2(next_outer.x - outer.x, next_outer.y - outer.y);
    float prev_heading = atan2(outer.x - prev_outer.x, outer.y - prev_outer.y);

    inner_points.push_back(Point(
        outer.x + cos(outer_heading) * width + cos(prev_heading) * width,
        outer.y - sin(outer_heading) * width - sin(prev_heading) * width));
  }

  return inner_points;
}
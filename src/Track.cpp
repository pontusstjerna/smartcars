#include "track.h"

#include <math.h>

Track::Track(string name, b2World *phys_world) : width(40), height(30)
{
  create_track(name, phys_world);
}

Track::Track(b2World *phys_world) : Track("default", phys_world) {}

Track::~Track()
{
  delete goal_line;
  segments.clear();
}

vector<TrackSegment> Track::get_segments()
{
  return segments;
}

GoalLine *Track::get_goal_line()
{
  return goal_line;
}

void Track::create_track(string name, b2World *phys_world)
{
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

    goal_line = new GoalLine(outer_points[0].add(track_width, 0), inner_points[0], phys_world);

    segments = vector<TrackSegment>{
        TrackSegment(outer_points, phys_world),
        TrackSegment(inner_points, phys_world)};
  }
}

// This is a test for the future when auto-generating tracks
vector<Point> Track::create_inner_points(vector<Point> outer_points)
{
  vector<Point> inner_points;
  for (int i = 0; i < outer_points.size(); i++)
  {
    Point prev_outer = i > 0 ? outer_points[i - 1] : outer_points[outer_points.size() - 2];
    Point outer = outer_points[i];
    Point next_outer = i < outer_points.size() - 1 ? outer_points[i + 1] : outer_points[0];

    float next_heading = outer.get_heading(next_outer);
    float prev_heading = prev_outer.get_heading(outer);

    // This formula is written in bug blood
    inner_points.insert(
        inner_points.begin(),
        outer.add(
            track_width * cos(next_heading) + track_width * cos(prev_heading),
            track_width * -sin(next_heading) + track_width * -sin(prev_heading)));
  }

  return inner_points;
}
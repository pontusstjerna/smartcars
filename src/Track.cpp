#include "track.h"

#include <math.h>

Track::Track(string name, b2World *phys_world)
{
  create_track(name, phys_world);
}

Track::Track(b2World *phys_world) : Track("default", phys_world) {}

Track::~Track()
{
  delete goal_line;
  for (TrackSegment *segment : segments)
  {
    delete segment;
  }
  segments.clear();
}

vector<TrackSegment *> Track::get_segments()
{
  return segments;
}

GoalLine *Track::get_goal_line()
{
  return goal_line;
}

float Track::get_width()
{
  return width;
}

float Track::get_height()
{
  return height;
}

Point Track::get_car_start_pos(int car_index)
{
  return ((Point[]){Point(2.2, 2.2), Point(5, 2.2)})[car_index];
}

float Track::get_car_start_rot(int car_index)
{
  return 0;
}

void Track::create_track(string name, b2World *phys_world)
{
  if (name == "default")
  {
    width = 40;
    height = 30;

    vector<Point> outer_points = {
        Point(0.5f, 0.5f),
        Point(0.5f, height - 0.5f),
        Point(width - 0.5f, height - 0.5f),
        Point(width - 0.5f, height / 2 + 1),
        Point(15, height / 2 + 1),
        Point(15, (height / 2) - 1),
        Point(width - 0.5f, (height / 2) - 1),
        Point(width - 0.5f, 0.5f),
        Point(0.5f, 0.5f)};

    vector<Point> inner_points = create_inner_points(outer_points);

    goal_line = new GoalLine(inner_points[0], outer_points[0].add(track_width, 0), phys_world);

    segments = vector<TrackSegment *>{
        new TrackSegment(outer_points, phys_world),
        new TrackSegment(inner_points, phys_world)};
  }
  else if (name == "car_test")
  {
    width = 20;
    height = 20;

    vector<Point> outer_points = {
        Point(0.5f, 0.5f),
        Point(0.5f, height - 0.5f),
        Point(width - 0.5f, height - 0.5f),
        Point(width - 0.5f, 0.5f),
        Point(0.5f, 0.5f)};

    vector<Point> inner_points = create_inner_points(outer_points);

    goal_line = new GoalLine(inner_points[0], outer_points[0].add(track_width, 0), phys_world);

    segments = vector<TrackSegment *>{
        new TrackSegment(outer_points, phys_world),
        new TrackSegment(inner_points, phys_world)};
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
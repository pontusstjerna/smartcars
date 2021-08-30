#ifndef TRACK
#define TRACK

#include "track_segment.h"
#include "goal_line.h"

#include <vector>
#include <string>
#include <box2d/box2d.h>

using namespace std;

class Track
{
public:
  Track(string name, b2World *phys_world);
  Track(b2World *phys_world);
  ~Track();

  const float width, height;

  vector<TrackSegment *> get_segments();
  GoalLine *get_goal_line();

private:
  const float track_width = 6;
  vector<TrackSegment *> segments;
  GoalLine *goal_line;

  void create_track(string name, b2World *phys_world);
  vector<Point> create_inner_points(vector<Point> outer_points);
};

#endif /* TRACK */

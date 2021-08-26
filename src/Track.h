#ifndef TRACK
#define TRACK

#include "track_segment.h"

#include <vector>
#include <string>
#include <box2d/box2d.h>

using namespace std;

class Track
{
public:
  Track(string name, b2World *phys_world);
  Track(b2World *phys_world);

  const float width, height;

  vector<TrackSegment> get_segments();

private:
  vector<TrackSegment> create_track(string name, b2World *phys_world);
  vector<TrackSegment> segments;
};

#endif /* TRACK */

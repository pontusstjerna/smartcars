#ifndef TRACK
#define TRACK

#include <vector>
#include "track_segment.h"
#include <string>

using namespace std;

class Track
{
public:
  Track(string name);
  Track();

  const float width, height;

  vector<TrackSegment> get_segments();

private:
  vector<TrackSegment> create_track(string name);
  vector<TrackSegment> segments;
};

#endif /* TRACK */

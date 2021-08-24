#ifndef TRACK
#define TRACK

#include <vector>
#include "TrackSegment.h"
#include <string>

using namespace std;

class Track
{
public:
  Track(string name);
  Track();

  const int width, height;

  vector<TrackSegment> get_segments();

private:
  vector<TrackSegment> create_track(string name);
  vector<TrackSegment> segments;
};

#endif /* TRACK */

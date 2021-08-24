#ifndef TRACK
#define TRACK

#include <vector>
#include "TrackSegment.h"

using namespace std;

class Track
{
public:
  vector<TrackSegment> get_segments();
};

#endif /* TRACK */

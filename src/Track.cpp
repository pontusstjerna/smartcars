#include "Track.h"

Track::Track(string name) : segments(create_track(name)) {}

Track::Track() : Track("default") {}

vector<TrackSegment> Track::create_track(string name)
{
  if (name == "default")
  {
    vector<TrackSegment> track = {TrackSegment(Point(0, 0), Point(300, 250))};
    track.push_back(TrackSegment(track.back(), Point(50, 50)));
    return track;
  }
}
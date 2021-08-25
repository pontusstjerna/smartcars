#include "track.h"

Track::Track(string name) : width(40), height(30)
{
  segments = create_track(name);
}

Track::Track() : Track("default") {}

vector<TrackSegment> Track::get_segments()
{
  return segments;
}

vector<TrackSegment> Track::create_track(string name)
{
  if (name == "default")
  {
    vector<TrackSegment> track = {TrackSegment(Point(1, 1), Point(20, 1))};
    track.push_back(TrackSegment(track.back(), Point(20, 20)));
    track.push_back(TrackSegment(track.back(), Point(10, 30)));
    track.push_back(TrackSegment(track.back(), Point(width - 1, height - 1)));
    return track;
  }
}
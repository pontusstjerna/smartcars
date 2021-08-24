#ifndef TRACKSEGMENT
#define TRACKSEGMENT

#include "Point.h"

struct TrackSegment
{
  Point start;
  Point end;
  TrackSegment(Point start, Point end) : start(start), end(end) {}
  TrackSegment(TrackSegment prev, Point next) : TrackSegment(prev.end, next) {}
};

#endif /* TRACKSEGMENT */

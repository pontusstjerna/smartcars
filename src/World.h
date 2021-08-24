#ifndef WORLD
#define WORLD

#include "Track.h"

class World
{
public:
  Track get_track();
  World();
  ~World();

private:
  Track track;
};

#endif /* WORLD */

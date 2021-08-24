#include "World.h"

World::World()
{
  track = new Track();
}

World::~World()
{
  delete track;
}

Track *World::get_track()
{
  return track;
}

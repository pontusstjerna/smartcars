#include "world.h"

World::World()
{
  track = new Track();
  cars = {Car(50, 50, 0)};
}

World::~World()
{
  delete track;
}

Track *World::get_track()
{
  return track;
}

vector<Car> World::get_cars()
{
  return cars;
}

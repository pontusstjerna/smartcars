#ifndef WORLD
#define WORLD

#include "track.h"
#include "car.h"
#include <vector>

using namespace std;

class World
{
public:
  World();
  ~World();

  Track *get_track();
  vector<Car> get_cars();

private:
  Track *track;
  vector<Car> cars;
};

#endif /* WORLD */

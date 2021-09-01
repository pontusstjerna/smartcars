#ifndef WORLD
#define WORLD

#include "track.h"
#include "car.h"
#include "contact_listener.h"

#include <vector>
#include <box2d/box2d.h>

using namespace std;

class World
{
public:
  static const int max_laps = 3;

  World();
  ~World();

  void update(float d_time);
  Track *get_track() const;
  vector<Car *> get_cars() const;

private:
  b2World *phys_world;
  Track *track;
  vector<Car *> cars;
  vector<int> laps;
  ContactListener *contact_listener;

  float timestep = 1.0f / 60.0f;
  float accumulator = 0;
  int32 velocity_iterations = 6;
  int32 position_iterations = 2;
};

#endif /* WORLD */

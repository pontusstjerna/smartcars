#ifndef WORLD
#define WORLD

#include "track.h"
#include "car.h"
#include "contact_listener.h"
#include "car_controller.h"

#include <vector>
#include <box2d/box2d.h>
#include <functional>

using namespace std;

class World
{
public:
  static const int max_laps = 1;

  World(vector<CarController *> car_controllers);
  ~World();

  void update(float d_time);
  Track *get_track() const;
  vector<Car *> get_cars() const;
  int get_laps(int car_index) const;
  float get_time(int car_index) const;
  bool all_finished() const;
  int get_winner_car_index() const;
  void set_debug_draw(b2Draw *debug_view);
  void update_debug_draw();

private:
  b2World *phys_world;
  Track *track;
  vector<Car *> cars;
  vector<int> laps;
  vector<float> car_times;
  ContactListener *contact_listener;

  float timestep = 1.0f / 60.0f;
  float accumulator = 0;
  int32 velocity_iterations = 6;
  int32 position_iterations = 2;
  int winner_car_index = -1;
};

#endif /* WORLD */

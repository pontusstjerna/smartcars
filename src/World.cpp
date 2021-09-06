#include "world.h"
#include "contact_listener.h"

World::World(vector<CarController *> car_controllers)
{
  b2Vec2 gravity(0.0f, 0.0f);
  phys_world = new b2World(gravity);

  track = new Track("default", phys_world);

  for (int i = 0; i < car_controllers.size(); i++)
  {

    Car *car = new Car(track->get_car_start_pos(i), track->get_car_start_rot(i), phys_world, i);
    cars.push_back(car);
    car_controllers[i]->set_car(car);
  }

  laps = vector<int>(cars.size(), 0);
  car_times = vector<float>(cars.size(), 0);

  contact_listener = new ContactListener(
      cars.size(),
      [=](int car_index)
      {
        laps[car_index]++;
        if (winner_car_index == -1)
        {
          winner_car_index = car_index;
        }
      });
  phys_world->SetContactListener(contact_listener);
}

World::~World()
{
  for (Car *car : cars)
  {
    delete car;
  }
  cars.clear();
  delete track;
  delete phys_world;
  delete contact_listener;
}

void World::update(float d_time)
{
  accumulator += d_time;
  while (accumulator >= timestep)
  {
    phys_world->Step(timestep, velocity_iterations, position_iterations);
    accumulator -= timestep;
  }

  for (int i = 0; i < cars.size(); i++)
  {
    cars[i]->update(d_time);

    if (laps[i] < max_laps)
    {
      car_times[i] += d_time;
    }
  }
}

Track *World::get_track() const
{
  return track;
}

vector<Car *> World::get_cars() const
{
  return cars;
}

int World::get_laps(int car_index) const
{
  return laps[car_index];
}

bool World::all_finished() const
{
  bool all_finished = true;
  for (int l : laps)
  {
    all_finished = l == max_laps;
    if (!all_finished)
      return false;
  }
  return true;
}

float World::get_time(int car_index) const
{
  return car_times[car_index];
}

int World::get_winner_car_index() const
{
  return winner_car_index;
}

void World::set_debug_draw(b2Draw *debug_view)
{
  phys_world->SetDebugDraw(debug_view);
  debug_view->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
}

void World::update_debug_draw()
{
  phys_world->DebugDraw();
}

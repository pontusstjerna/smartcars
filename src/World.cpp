#include "world.h"
#include "contact_listener.h"

World::World()
{
  b2Vec2 gravity(0.0f, 0.0f);
  phys_world = new b2World(gravity);

  track = new Track(phys_world);
  cars = {new Car(phys_world, 2.2, 2.2, 0), new Car(phys_world, 5, 2.2, 0)};

  contact_listener = new ContactListener();
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

  for (Car *car : cars)
  {
    car->update(d_time);
  }
}

Track *World::get_track()
{
  return track;
}

vector<Car *> World::get_cars()
{
  return cars;
}

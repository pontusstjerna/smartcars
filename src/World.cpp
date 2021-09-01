#include "world.h"
#include "contact_listener.h"

#include <iostream>

World::World()
{
  b2Vec2 gravity(0.0f, 0.0f);
  phys_world = new b2World(gravity);

  track = new Track(phys_world);
  cars = {new Car(2.2, 2.2, 0, phys_world, 0), new Car(5, 2.2, 0, phys_world, 1)};

  laps = vector<int>(cars.size(), 0);

  contact_listener = new ContactListener(
      cars.size(),
      [=](int car_index)
      {
        laps[car_index]++;
        std::cout << "Car " << car_index << " new lap!\n";
        std::cout << "Current score: \n";
        for (int i = 0; i < laps.size(); i++)
        {
          std::cout << "Car " << i << ": " << laps[i] << "/" << max_laps << endl;
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

  for (Car *car : cars)
  {
    car->update(d_time);
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

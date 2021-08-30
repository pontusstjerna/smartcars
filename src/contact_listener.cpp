#define _USE_MATH_DEFINES
#include <math.h>

#include "contact_listener.h"
#include "body_data.h"
#include "goal_line.h"
#include "car.h"

#include <iostream>

using namespace std;

ContactListener::ContactListener(int n_cars)
{
  potential_laps = vector<bool>(n_cars, false);
}

void ContactListener::BeginContact(b2Contact *contact)
{
  b2Body *body_a = contact->GetFixtureA()->GetBody();
  b2Body *body_b = contact->GetFixtureB()->GetBody();

  if (is_potential_lap(body_a, body_b))
  {
    int car_index = try_get_car_index(body_a, body_b);
    if (car_index >= 0)
    {
      potential_laps[car_index] = true;
    }
  }
}

void ContactListener::EndContact(b2Contact *contact)
{
  b2Body *body_a = contact->GetFixtureA()->GetBody();
  b2Body *body_b = contact->GetFixtureB()->GetBody();

  if (is_potential_lap(body_a, body_b))
  {
    int car_index = try_get_car_index(body_a, body_b);
    if (car_index >= 0)
    {
      if (potential_laps[car_index])
      {
        potential_laps[car_index] = false;
        cout << "We have a lap!\n";
      }
    }
  }
}

bool ContactListener::is_potential_lap(b2Body *body_a, b2Body *body_b)
{

  PhysObject *a = cast_to_phys_obj(body_a);
  PhysObject *b = cast_to_phys_obj(body_b);

  GoalLine *goal_line = NULL;
  b2Body *car_body = NULL;

  if (a->body_data.body_type == BodyType::CAR && b->body_data.body_type == BodyType::GOAL_LINE)
  {
    car_body = body_a;
    goal_line = (GoalLine *)b;
  }
  else if (a->body_data.body_type == BodyType::GOAL_LINE && b->body_data.body_type == BodyType::CAR)
  {
    goal_line = (GoalLine *)a;
    car_body = body_b;
  }
  else
  { // We know that some of the colliding objects is not a car nor a goal line
    return false;
  }

  float goal_line_heading = goal_line->start.get_heading(goal_line->end);
  float car_heading = car_body->GetAngle();

  // cout << "Car heading: " << car_heading << " - goal line heading: " << goal_line_heading << endl;

  return car_heading > goal_line_heading + M_PI && car_heading < goal_line_heading + 2 * M_PI;
}

PhysObject *ContactListener::cast_to_phys_obj(b2Body *body)
{
  return (PhysObject *)body->GetUserData().pointer;
}

int ContactListener::try_get_car_index(b2Body *body_a, b2Body *body_b)
{
  BodyData a = cast_to_phys_obj(body_a)->body_data;
  BodyData b = cast_to_phys_obj(body_b)->body_data;

  if (a.body_type == BodyType::CAR && b.body_type == BodyType::CAR) // Both cars
  {
    return -1;
  }
  else if (a.body_type == BodyType::CAR)
  {
    return a.index;
  }
  else if (b.body_type == BodyType::CAR)
  {
    return b.index;
  }

  return -1;
}

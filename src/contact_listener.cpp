#define _USE_MATH_DEFINES
#include <math.h>

#include "contact_listener.h"
#include "body_data.h"
#include "goal_line.h"
#include "car.h"

#include <iostream>

using namespace std;

ContactListener::ContactListener(int n_cars, function<void(int)> on_lap) : on_lap(on_lap)
{
  potential_laps = vector<bool>(n_cars, false);
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *old_manifold)
{
  b2Body *body_a = contact->GetFixtureA()->GetBody();
  b2Body *body_b = contact->GetFixtureB()->GetBody();

  if (is_wheel_and_goal_line(body_a, body_b))
  {
    contact->SetEnabled(false);
    return;
  }

  if (is_potential_lap(body_a, body_b, true))
  {
    contact->SetEnabled(false);
    int car_index = try_get_car_index(body_a, body_b);
    if (car_index >= 0)
    {
      potential_laps[car_index] = true;
    }
  }
  else
  {
    int car_index = try_get_car_index(body_a, body_b);
    if (car_index >= 0 && potential_laps[car_index]) // Keep disabling until we've ended contact
    {
      contact->SetEnabled(false);
    }
  }
}

void ContactListener::BeginContact(b2Contact *contact)
{
}

void ContactListener::EndContact(b2Contact *contact)
{
  b2Body *body_a = contact->GetFixtureA()->GetBody();
  b2Body *body_b = contact->GetFixtureB()->GetBody();

  if (is_potential_lap(body_a, body_b, false))
  {
    int car_index = try_get_car_index(body_a, body_b);
    if (car_index >= 0)
    {
      if (potential_laps[car_index])
      {
        potential_laps[car_index] = false;
        on_lap(car_index);
      }
    }
  }
}

bool ContactListener::is_potential_lap(b2Body *body_a, b2Body *body_b, bool is_begin)
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

  b2Vec2 goal_line_vector = b2Vec2(goal_line->end.sub(goal_line->start).to_b2Vec2());
  goal_line_vector.Normalize();

  // Vector relative from goal line start point
  b2Vec2 goal_line_car_pos = car_body->GetPosition();
  goal_line_car_pos -= goal_line->start.to_b2Vec2();
  goal_line_car_pos.Normalize();

  // Rotate 90 deg CCW
  b2Vec2 goal_line_car_pos_rotated = goal_line_car_pos.Skew();
  /* Dot product > 0 is if vector is "in front of us", i.e. car vel is in front of goal line.
     By rotating the car's velocity 90 deg CCW we can calculate wether the vector is on the "right" or "left" side of goal line
  */
  float dot = b2Dot(goal_line_vector, goal_line_car_pos_rotated);

  /*cout << (is_begin ? "Begin contact: " : "End contact: ");
  cout << "Dot product of car x goal line is: " << dot << endl;
  cout << "Goal line car pos vector: (" << goal_line_car_pos.x << ", " << goal_line_car_pos.y << ")\n";*/

  // Beginning of contact? Car must be to the left of goal line. End of contact? Must be to the right.
  return is_begin ? dot < 0 : dot > 0;
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

bool ContactListener::is_wheel_and_goal_line(b2Body *body_a, b2Body *body_b)
{
  BodyData a = cast_to_phys_obj(body_a)->body_data;
  BodyData b = cast_to_phys_obj(body_b)->body_data;

  return (a.body_type == BodyType::WHEEL && b.body_type == BodyType::GOAL_LINE) ||
         (b.body_type == BodyType::WHEEL && a.body_type == BodyType::GOAL_LINE);
}

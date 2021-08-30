#include "goal_line.h"
#include "body_data.h"

GoalLine::GoalLine(Point start, Point end, b2World *phys_world) : PhysObject(BodyData(BodyType::GOAL_LINE)), start(start), end(end)
{
  b2BodyDef body_def;
  body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  b2Body *body = phys_world->CreateBody(&body_def);

  float heading = end.get_heading(start);

  // Add 1 meter ghost goal line on both sides
  b2Vec2 first_ghost = start.add(-sin(heading), -cos(heading)).to_b2Vec2();
  b2Vec2 last_ghost = end.add(sin(heading), cos(heading)).to_b2Vec2();

  b2EdgeShape edge;
  // Build it inverted to allow passing from below
  edge.SetOneSided(last_ghost, end.to_b2Vec2(), start.to_b2Vec2(), first_ghost);

  b2FixtureDef fixture_def;
  fixture_def.shape = &edge;
  fixture_def.density = 1.0f;
  fixture_def.friction = 0.3f;

  body->CreateFixture(&fixture_def);
}

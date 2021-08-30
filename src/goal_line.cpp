#include "goal_line.h"
#include "body_data.h"

GoalLine::GoalLine(Point start, Point end, b2World *phys_world) : PhysObject(BodyData(BodyType::GOAL_LINE)), start(start), end(end)
{
  b2BodyDef body_def;
  body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
  b2Body *body = phys_world->CreateBody(&body_def);

  float heading = end.get_heading(start);

  b2EdgeShape edge;
  edge.SetTwoSided(start.to_b2Vec2(), end.to_b2Vec2());
  b2FixtureDef fixture_def;
  fixture_def.shape = &edge;
  fixture_def.density = 1.0f;
  fixture_def.friction = 0.3f;

  body->CreateFixture(&fixture_def);
}

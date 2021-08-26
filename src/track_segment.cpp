#include "track_segment.h"

using namespace std;

TrackSegment::TrackSegment(vector<Point> points, b2World *phys_world, Point prev_ghost, Point next_ghost) : points(points)
{
  // Create body
  b2Vec2 vertices[points.size()];
  for (int i = 0; i < points.size(); i++)
  {
    vertices[i] = points[i].to_b2Vec2();
  }

  b2ChainShape shape;
  shape.CreateChain(vertices, points.size(), prev_ghost.to_b2Vec2(), next_ghost.to_b2Vec2());

  b2BodyDef body_def;
  b2Body *body = phys_world->CreateBody(&body_def);

  b2FixtureDef fixture_def;
  fixture_def.shape = &shape;
  fixture_def.density = 1.0f;
  fixture_def.friction = 0.3f;
  body->CreateFixture(&fixture_def);
}

vector<Point> TrackSegment::get_points()
{
  return points;
}

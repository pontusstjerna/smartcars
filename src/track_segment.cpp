#include "track_segment.h"

using namespace std;

TrackSegment::TrackSegment(vector<Point> points, b2World *phys_world, Point prev_ghost, Point next_ghost) : points(points)
{
  b2ChainShape shape;
  b2Vec2 vertices[points.size()];
  create_vertices(vertices, points);
  shape.CreateChain(vertices, points.size(), prev_ghost.to_b2Vec2(), next_ghost.to_b2Vec2());

  // Reference to shape is not kept outside scope
  create_segment(&shape, phys_world);
}

TrackSegment::TrackSegment(vector<Point> points, b2World *phys_world) : points(points)
{
  b2ChainShape shape;
  b2Vec2 vertices[points.size()];
  create_vertices(vertices, points);
  shape.CreateLoop(vertices, points.size());

  create_segment(&shape, phys_world);
}

vector<Point> TrackSegment::get_points()
{
  return points;
}

void TrackSegment::create_segment(b2ChainShape *chain_shape, b2World *phys_world)
{
  b2BodyDef body_def;
  b2Body *body = phys_world->CreateBody(&body_def);

  b2FixtureDef fixture_def;
  fixture_def.shape = chain_shape;
  fixture_def.density = 1.0f;
  fixture_def.friction = 0.3f;
  body->CreateFixture(&fixture_def);
}

void TrackSegment::create_vertices(b2Vec2 *arr, vector<Point> points)
{
  for (int i = 0; i < points.size(); i++)
  {
    arr[i] = points[i].to_b2Vec2();
  }
}

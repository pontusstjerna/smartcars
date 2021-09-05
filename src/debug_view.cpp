#include "debug_view.h"

DebugView::DebugView(SDL_Renderer *renderer, float scale) : renderer(renderer), scale(scale) {}

void DebugView::DrawPolygon(const b2Vec2 *vertices, int32 vertex_count, const b2Color &color)
{
  for (int i = 0; i < vertex_count; i++)
  {
    b2Vec2 next = i == vertex_count - 1 ? vertices[0] : vertices[i + 1];
    SDL_RenderDrawLine(renderer,
                       (int)(vertices[i].x * scale),
                       (int)(vertices[i].y * scale),
                       (int)(next.x * scale),
                       (int)(next.y * scale));
  }
}

void DebugView::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertex_count, const b2Color &color)
{
  for (int i = 0; i < vertex_count; i++)
  {
    b2Vec2 next = i == vertex_count - 1 ? vertices[0] : vertices[i + 1];
    SDL_RenderDrawLine(renderer,
                       (int)(vertices[i].x * scale),
                       (int)(vertices[i].y * scale),
                       (int)(next.x * scale),
                       (int)(next.y * scale));
  }
}

void DebugView::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
{
  SDL_RenderDrawLine(renderer,
                     (int)(p1.x * scale),
                     (int)(p1.y * scale),
                     (int)(p2.x * scale),
                     (int)(p2.y * scale));
}

void DebugView::DrawCircle(const b2Vec2 &center, float radius, const b2Color &color)
{
}
void DebugView::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color)
{
}

void DebugView::DrawTransform(const b2Transform &xf)
{
}

void DebugView::DrawPoint(const b2Vec2 &p, float size, const b2Color &color)
{
  SDL_RenderDrawLine(renderer, p.x, p.y, p.x, p.y);
}
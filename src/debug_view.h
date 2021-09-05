#ifndef DEBUG_VIEW
#define DEBUG_VIEW

#include <box2d/box2d.h>
#include <SDL2/SDL.h>

class DebugView : public b2Draw
{
public:
  DebugView(SDL_Renderer *renderer, float scale);

  void DrawPolygon(const b2Vec2 *vertices, int32 vertex_count, const b2Color &color);
  void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertex_count, const b2Color &color);
  void DrawCircle(const b2Vec2 &center, float radius, const b2Color &color);
  void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color);
  void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
  void DrawTransform(const b2Transform &xf);
  void DrawPoint(const b2Vec2 &p, float size, const b2Color &color);

private:
  SDL_Renderer *renderer;
  const float scale;
};

#endif /* DEBUG_VIEW */

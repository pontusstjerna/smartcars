#ifndef VIEW
#define VIEW

#include "world.h"
#include "point.h"

#include <SDL2/SDL.h>

class View
{
public:
  View(World *world);
  ~View();
  void start();
  void init();
  void update();

private:
  World *world;

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *car_texture = NULL;

  float scale;
  const int WIDTH = 800;
  const int HEIGHT = 600;

  void draw_track();
  void draw_cars();
  void render_line(Point start, Point end);
};

#endif /* VIEW */

#ifndef VIEW
#define VIEW

#include "World.h"
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
  float scale;
  const int WIDTH = 800;
  const int HEIGHT = 600;

  void draw_track();
};

#endif /* VIEW */

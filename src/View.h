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

private:
  World *world;
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
};

#endif /* VIEW */

#ifndef GUI_VIEW
#define GUI_VIEW

#include "world.h"
#include "text_renderer.h"

#include <SDL2/SDL.h>

class GuiView
{
public:
  GuiView(World *world, SDL_Renderer *renderer);
  ~GuiView();

  void init();
  void render();

private:
  const World *world;
  const SDL_Renderer *renderer;

  TextRenderer *text_renderer;
};

#endif /* GUI_VIEW */

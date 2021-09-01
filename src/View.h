#ifndef VIEW
#define VIEW

#include "world.h"
#include "point.h"
#include "gui_view.h"

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

  GuiView *gui_view;

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *car_texture = NULL;

  float scale;
  int extra_x;
  int extra_y;
  const static int WIDTH = (int)(800 * 1.5f);
  const static int HEIGHT = (int)(600 * 1.5f);
  const static int GAME_WIDTH = (int)(700 * 1.5f);
  const static int GUI_WIDTH = WIDTH - GAME_WIDTH;

  void draw_track();
  void draw_cars();
  void render_line(Point start, Point end);
};

#endif /* VIEW */

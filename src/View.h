#ifndef VIEW
#define VIEW

#include "world.h"
#include "point.h"
#include "gui_view.h"
#include "debug_view.h"
#include "SDL_utils.h"
#include "dynamic_body.h"

#include <SDL2/SDL.h>

class View
{
public:
  View(World *world);
  ~View();
  void start();
  void init();
  void update(int fps, function<void()> draw_debug);
  DebugView *get_debug_view();

  const static int WIDTH = (int)(800 * 1.5f);
  const static int HEIGHT = (int)(600 * 1.5f);
  const static int GAME_WIDTH = (int)(700 * 1.5f);
  const static int GUI_WIDTH = WIDTH - GAME_WIDTH;

private:
  World *world;

  GuiView *gui_view;
  DebugView *debug_view;

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  SDL_utils::TextureWrapper car_texture;
  SDL_utils::TextureWrapper wheel_texture;
  SDL_utils::TextureWrapper goal_line_texture;
  SDL_utils::TextureWrapper track_segment_texture;

  float scale;
  int extra_x;
  int extra_y;

  void draw_track();
  void draw_cars();
  void render_line(Point start, Point end);
  void render_line(Point start, Point end, SDL_utils::TextureWrapper texture);
  void render_dynamic_body(DynamicBody *body, SDL_Texture *texture, bool flip);
};

#endif /* VIEW */

#include "view.h"
#include "SDL_utils.h"
#include "texture_sizes.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
using namespace SDL_utils;

View::View(World *world) : world(world)
{
  float world_width = world->get_track()->width;
  float world_height = world->get_track()->height;
  scale = min((float)WIDTH / world_width, (float)HEIGHT / world_height);
}

View::~View()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void View::init()
{
  string title = "Smart Cars";

  window = run_safe<SDL_Window *>(SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN));

  renderer = run_safe<SDL_Renderer *>(SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED));

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  car_texture = load_texture(renderer, "car");
}

void View::update()
{
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

  // Clear screen
  SDL_RenderClear(renderer);

  draw_track();

  draw_cars();

  // Render stuff on window
  SDL_RenderPresent(renderer);
}

void View::draw_track()
{
  SDL_SetRenderDrawColor(renderer, 50, 255, 50, SDL_ALPHA_OPAQUE);

  for (TrackSegment segment : world->get_track()->get_segments())
  {
    SDL_RenderDrawLine(
        renderer,
        (int)(segment.start.x * scale),
        (int)(segment.start.y * scale),
        (int)(segment.end.x * scale),
        (int)(segment.end.y * scale));
  }
}

void View::draw_cars()
{
  for (auto car : world->get_cars())
  {
    SDL_Rect source_rect = {0,
                            0,
                            TextureSizes::CAR_WIDTH,
                            TextureSizes::CAR_HEIGHT};

    SDL_Rect destination_rect = {(int)(car->get_x() * scale),
                                 (int)(car->get_y() * scale),
                                 (int)(car->width * scale),
                                 (int)(car->length * scale)};

    SDL_RenderCopyEx(
        renderer,
        car_texture,
        &source_rect,
        &destination_rect,
        (double)(car->get_rot()),
        NULL,
        SDL_FLIP_NONE);
  }
}
#include "View.h"
#include <iostream>
#include <string>
#include "SDL_utils.h"
#include <algorithm>

using namespace std;

View::View(World *world) : world(world)
{
  int world_width = world->get_track()->width;
  int world_height = world->get_track()->height;
  scale = min((float)WIDTH / (float)world_width, (float)HEIGHT / (float)world_height);
}

View::~View()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void View::init()
{
  string title = "Smart Cars";

  SDL_utils::run_safe(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer));
}

void View::update()
{
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

  // Clear screen
  SDL_RenderClear(renderer);

  draw_track();

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

#include "View.h"
#include <iostream>
#include <string>
#include "SDL_utils.h"

using namespace std;

View::View(World *world) : world(world) {}

View::~View()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void View::init()
{
  string title = "Smart Cars";

  SDL_utils::run_safe(SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer));
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

  auto segments = world->get_track()->segments;
  int size = segments.size();

  for (int i = 0; i < segments.size(); i++)
  {
    auto segment = segments[i];
    SDL_RenderDrawLine(renderer, segment.start.x, segment.start.y, segment.end.x, segment.end.y);
  }
}

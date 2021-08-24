#include "View.h"
#include <iostream>
#include <string>

using namespace std;

View::View(World *world) : world(world) {}

View::~View()
{
  SDL_DestroyWindow(window);
}

void View::init()
{
  string title = "Smart Cars";
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    throw SDL_GetError();
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    throw SDL_GetError();
  }

  SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
}

void View::update()
{
  // Clear screen
  SDL_RenderClear(renderer);

  // Render stuff on window
  SDL_RenderPresent(renderer);
}
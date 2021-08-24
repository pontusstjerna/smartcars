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
}
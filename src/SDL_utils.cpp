#include "SDL_utils.h"
#include <SDL2/SDL.h>

void SDL_utils::exec(int (*function)(Uint32))
{
  if (function(1) == -1)
  {
    throw SDL_GetError();
  }
}

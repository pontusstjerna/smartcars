#ifndef SDL_UTILS
#define SDL_UTILS

#include <SDL2/SDL.h>
namespace SDL_utils
{
  void exec(int (*function)(Uint32));
}

#endif /* SDL_UTILS */

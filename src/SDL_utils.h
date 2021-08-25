#ifndef SDL_UTILS
#define SDL_UTILS

#include <SDL2/SDL.h>
#include <string>

namespace SDL_utils
{
  void run_safe(int result);
  SDL_Texture *load_texture(SDL_Renderer *renderer, std::string name);
}

#endif /* SDL_UTILS */

#ifndef SDL_UTILS
#define SDL_UTILS

#include <SDL2/SDL.h>
#include <string>

namespace SDL_utils
{
  void run_safe(int result);
  SDL_Texture *load_texture(SDL_Renderer *renderer, std::string name);

  // Template functions - have to define in header :(
  template <typename T>
  T run_safe(T result)
  {
    if (result == NULL)
    {
      throw "SDL error: " + std::string(SDL_GetError()) + "\n";
    }
  }
}

#endif /* SDL_UTILS */

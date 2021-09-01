#ifndef SDL_UTILS
#define SDL_UTILS

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace SDL_utils
{
  struct TextureWrapper
  {
    SDL_Texture *texture;
    int width = 0;
    int height = 0;

    TextureWrapper(
        SDL_Texture *texture, int width, int height)
        : texture(texture),
          width(width),
          height(height) {}
  };

  void run_safe(int result);
  TextureWrapper load_texture(SDL_Renderer *renderer, std::string name);
  TextureWrapper load_text_texture(SDL_Renderer *renderer, std::string text, SDL_Color text_color, TTF_Font *font);

  // Template functions - have to define in header :(
  template <typename T>
  T run_safe(T result)
  {
    if (result == NULL)
    {
      throw "SDL error: " + std::string(SDL_GetError()) + "\n";
    }

    return result;
  }
};

#endif /* SDL_UTILS */

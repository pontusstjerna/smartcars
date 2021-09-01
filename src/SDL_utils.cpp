#include "SDL_utils.h"
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;

SDL_utils::TextureWrapper load_texture_from_surface(SDL_Surface *surface, SDL_Renderer *renderer)
{
  SDL_Texture *texture = NULL;

  if (surface == NULL)
  {
    throw "Texture error: " + string(IMG_GetError()) + "\n";
  }

  texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (texture == NULL)
  {
    throw "Texture error: " + string(IMG_GetError()) + "\n";
  }

  int width = surface->w;
  int height = surface->h;

  SDL_FreeSurface(surface);

  return SDL_utils::TextureWrapper(texture, width, height);
}

void SDL_utils::run_safe(int result)
{
  if (result != 0)
  {
    throw "SDL error: " + string(SDL_GetError()) + "\n";
  }
}

SDL_utils::TextureWrapper SDL_utils::load_texture(SDL_Renderer *renderer, string name)
{
  string full_path_name = "assets/textures/" + name + ".png";

  SDL_Surface *tmp_texture_surface = IMG_Load(full_path_name.c_str());

  SDL_utils::TextureWrapper texture_wrapper = load_texture_from_surface(tmp_texture_surface, renderer);

  cout << "Loaded texture " << full_path_name << "\n";

  return texture_wrapper;
}

SDL_utils::TextureWrapper SDL_utils::load_text_texture(SDL_Renderer *renderer, string text, SDL_Color text_color, TTF_Font *font)
{
  SDL_Surface *tmp_text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);

  return load_texture_from_surface(tmp_text_surface, renderer);
}

#include "SDL_utils.h"
#include <string>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

void SDL_utils::run_safe(int result)
{
  if (result != 0)
  {
    throw "SDL error: " + string(SDL_GetError()) + "\n";
  }
}

SDL_Texture *SDL_utils::load_texture(SDL_Renderer *renderer, string name)
{
  SDL_Texture *texture = NULL;
  string full_path_name = "assets/textures/" + name + ".png";

  SDL_Surface *tmp_texture_surface = IMG_Load(full_path_name.c_str());

  if (tmp_texture_surface == NULL)
  {
    throw "Texture error: " + string(IMG_GetError()) + "\n";
  }

  texture = SDL_CreateTextureFromSurface(renderer, tmp_texture_surface);

  if (texture == NULL)
  {
    throw "Texture error: " + string(IMG_GetError()) + "\n";
  }

  SDL_FreeSurface(tmp_texture_surface);

  cout << "Loaded texture " << full_path_name << "\n";

  return texture;
}

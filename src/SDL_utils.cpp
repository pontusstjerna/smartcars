#include "SDL_utils.h"
#include <string>
#include <SDL2/SDL.h>

using namespace std;

void SDL_utils::run_safe(int result)
{
  if (result != 0)
  {
    throw "SDL error: " + string(SDL_GetError()) + "\n";
  }
}

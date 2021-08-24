#ifndef INPUT_CONTROLLER
#define INPUT_CONTROLLER

#include <SDL2/SDL.h>

class InputController
{
public:
  void check_inputs(SDL_Event *event);
};

#endif /* INPUT_CONTROLLER */

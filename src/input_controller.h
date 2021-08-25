#ifndef INPUT_CONTROLLER
#define INPUT_CONTROLLER

#include "car.h"

#include <SDL2/SDL.h>

class InputController
{
public:
  InputController(Car *car);
  void check_inputs(SDL_Event *event);

private:
  Car *car;
};

#endif /* INPUT_CONTROLLER */

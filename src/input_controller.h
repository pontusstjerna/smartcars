#ifndef INPUT_CONTROLLER
#define INPUT_CONTROLLER

#include "car_controller.h"

#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class InputController
{
public:
  InputController(vector<CarController *> human_controllers);
  void check_inputs(SDL_Event *event);

private:
  vector<CarController *> controllers;
};

#endif /* INPUT_CONTROLLER */

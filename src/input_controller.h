#ifndef INPUT_CONTROLLER
#define INPUT_CONTROLLER

#include "car.h"

#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class InputController
{
public:
  InputController(vector<Car *> human_cars);
  void check_inputs(SDL_Event *event);

private:
  vector<Car *> cars;
};

#endif /* INPUT_CONTROLLER */

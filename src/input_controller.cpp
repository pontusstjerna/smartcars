#include "input_controller.h"

InputController::InputController(vector<CarController *> human_controllers) : controllers(human_controllers) {}

void InputController::check_inputs(SDL_Event *event)
{
  if (event->type == SDL_KEYDOWN)
  {
    switch (event->key.keysym.sym)
    {
    case SDLK_UP:
      controllers[0]->accelerate();
      break;
    case SDLK_w:
      controllers[1]->accelerate();
      break;
    case SDLK_DOWN:
      controllers[0]->reverse();
      break;
    case SDLK_s:
      controllers[1]->reverse();
      break;
    case SDLK_LEFT:
      controllers[0]->turn_left();
      break;
    case SDLK_a:
      controllers[1]->turn_left();
      break;
    case SDLK_RIGHT:
      controllers[0]->turn_right();
      break;
    case SDLK_d:
      controllers[1]->turn_right();
      break;
    }
  }
  else if (event->type == SDL_KEYUP)
  {
    switch (event->key.keysym.sym)
    {
    case SDLK_ESCAPE:
      // Mutate event type (bad practice?)
      event->type = SDL_QUIT;
      break;
    case SDLK_UP:
    case SDLK_DOWN:
      controllers[0]->release();
      break;
    case SDLK_w:
    case SDLK_s:
      controllers[1]->release();
      break;
    case SDLK_LEFT:
    case SDLK_RIGHT:
      controllers[0]->stop_turn();
      break;
    case SDLK_a:
    case SDLK_d:
      controllers[1]->stop_turn();
      break;
    }
  }
}

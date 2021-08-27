#include "input_controller.h"

InputController::InputController(vector<Car *> human_cars) : cars(human_cars) {}

void InputController::check_inputs(SDL_Event *event)
{
  if (event->type == SDL_KEYDOWN)
  {
    switch (event->key.keysym.sym)
    {
    case SDLK_UP:
      cars[0]->accelerate();
      break;
    case SDLK_w:
      cars[1]->accelerate();
      break;
    case SDLK_DOWN:
      cars[0]->reverse();
      break;
    case SDLK_s:
      cars[1]->reverse();
      break;
    case SDLK_LEFT:
      cars[0]->turn_left();
      break;
    case SDLK_a:
      cars[1]->turn_left();
      break;
    case SDLK_RIGHT:
      cars[0]->turn_right();
      break;
    case SDLK_d:
      cars[1]->turn_right();
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
      cars[0]->stop();
      break;
    case SDLK_w:
    case SDLK_s:
      cars[1]->stop();
      break;
    case SDLK_LEFT:
    case SDLK_RIGHT:
      cars[0]->stop_turn();
      break;
    case SDLK_a:
    case SDLK_d:
      cars[1]->stop_turn();
      break;
    }
  }
}

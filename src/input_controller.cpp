#include "input_controller.h"

InputController::InputController(Car *car) : car(car) {}

void InputController::check_inputs(SDL_Event *event)
{
  if (event->type == SDL_KEYDOWN)
  {
    switch (event->key.keysym.sym)
    {
    case SDLK_UP:
      car->accelerate();
      break;
    case SDLK_DOWN:
      car->reverse();
      break;
    case SDLK_LEFT:
      car->turn_left();
      break;
    case SDLK_RIGHT:
      car->turn_right();
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
      car->stop();
      break;
    case SDLK_LEFT:
    case SDLK_RIGHT:
      car->stop_turn();
      break;
    }
  }
}

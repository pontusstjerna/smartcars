#include "input_controller.h"

void InputController::check_inputs(SDL_Event *event)
{
  if (event->type == SDL_KEYDOWN)
  {
    switch (event->key.keysym.sym)
    {
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
    }
  }
}

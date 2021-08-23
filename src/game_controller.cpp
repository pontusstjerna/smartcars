#include "game_controller.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL_utils.h"
#include <string>

using namespace std;

void GameController::start_game()
{
  cout << "Starting game...";

  try
  {
    SDL_utils::exec(&SDL_Init);
  }
  catch (string error)
  {
    cout << error;
    return;
  }
}

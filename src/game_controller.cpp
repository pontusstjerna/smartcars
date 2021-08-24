#include "game_controller.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL_utils.h"
#include <string>

using namespace std;

GameController::GameController() {}

GameController::~GameController()
{
  cout << "Quitting game...";
  delete view;
  delete world;
  SDL_Quit();
  cout << "done!";
}

void GameController::start_game()
{
  cout << "Starting game...\n";

  try
  {
    SDL_utils::run_safe(SDL_Init(SDL_INIT_EVERYTHING));
  }
  catch (string error)
  {
    cout << error;
    return;
  }

  world = new World();
  view = new View(world);
  view->init();
  SDL_Delay(3000);
}

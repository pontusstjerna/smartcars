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
  try
  {
    view->init();
  }
  catch (string error)
  {
    cout << error;
    return;
  }

  run_game();
}

void GameController::run_game()
{
  SDL_Event event;
  bool running = true;

  // Game loop
  while (running)
  {
    while (SDL_PollEvent(&event) != 0)
    {
      running = event.type != SDL_QUIT;
    }
    view->update();
    SDL_Delay(10);
  }
}

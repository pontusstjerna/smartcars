#include "game_controller.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SDL_utils.h"
#include <string>

using namespace std;

GameController::GameController() {}

GameController::~GameController()
{
  cout << "Quitting game...";
  delete view;
  delete world;
  delete input_controller;
  TTF_Quit();
  IMG_Quit();
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

  // TODO: only get player controlled cars
  input_controller = new InputController(world->get_cars());

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

  float d_time = 0;
  float current_time = 0;
  float prev_time = 0;

  // Game loop
  while (running)
  {
    while (running && SDL_PollEvent(&event) != 0)
    {
      input_controller->check_inputs(&event);
      running = event.type != SDL_QUIT;
    }

    world->update(d_time);
    view->update();

    SDL_Delay(10);

    current_time = SDL_GetTicks() / 1000.0f;
    d_time = current_time - prev_time;
    prev_time = current_time;
  }
}

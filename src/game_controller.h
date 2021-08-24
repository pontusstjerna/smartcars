#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include "World.h"
#include "View.h"
#include "input_controller.h"

class GameController
{
public:
  GameController();
  ~GameController();
  void start_game();

private:
  World *world;
  View *view;
  InputController input_controller;

  void run_game();
};

#endif /* GAME_CONTROLLER */

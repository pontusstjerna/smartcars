#ifndef GAME_CONTROLLER
#define GAME_CONTROLLER

#include "World.h"
#include "View.h"

class GameController
{
public:
  GameController();
  ~GameController();
  void start_game();

private:
  World *world;
  View *view;
};

#endif /* GAME_CONTROLLER */

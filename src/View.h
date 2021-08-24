#ifndef VIEW
#define VIEW

#include "World.h"

class View
{
public:
  View(World *world);
  ~View();
  void start();

private:
  World *world;
};

#endif /* VIEW */

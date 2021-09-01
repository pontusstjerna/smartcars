#include "gui_view.h"

#include <string>

using namespace std;

GuiView::GuiView(World *world, SDL_Renderer *renderer) : world(world), renderer(renderer)
{
  text_renderer = new TextRenderer(renderer);
}

GuiView::~GuiView()
{
  delete text_renderer;
}

void GuiView::init()
{
  text_renderer->init();
}

void GuiView::render(int fps)
{
  text_renderer->render_small_text("FPS: " + to_string(fps), 2, 2);
  text_renderer->render_bold_text("SmartCars", 10, 30);

  auto cars = world->get_cars();

  for (int i = 0; i < cars.size(); i++)
  {
    auto car = cars[i];
    text_renderer->render_text(
        "Car " + to_string(i + 1) + ": " + to_string(world->get_laps(i)) + "/" + to_string(world->max_laps),
        10, 70 + 30 * i);
  }
}
#include "gui_view.h"
#include "view.h"

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
  int margin_xs = 30;
  int margin_s = 30;
  int margin_l = 70;

  text_renderer->render_small_text("FPS: " + to_string(fps), 2, 2);
  text_renderer->render_bold_text("SmartCars", 10, margin_s);

  auto cars = world->get_cars();

  for (int i = 0; i < cars.size(); i++)
  {
    auto car = cars[i];
    text_renderer->render_text(
        "Car " + to_string(i + 1) + ": " + to_string(world->get_laps(i)) + "/" + to_string(world->max_laps),
        10, margin_l + margin_l * i);
    text_renderer->render_small_text(
        "Time: " + to_string(world->get_time(i)) + "s", 10, margin_l + margin_l * i + margin_s);
  }

  int winner_index = world->get_winner_car_index();
  if (winner_index >= 0)
  {
    text_renderer->render_bold_text("CAR " + to_string(winner_index + 1) + " WINS!", View::WIDTH / 2, margin_xs);
  }
}
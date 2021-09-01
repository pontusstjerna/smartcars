#include "view.h"
#include "SDL_utils.h"
#include "texture_sizes.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
using namespace SDL_utils;

View::View(World *world) : world(world)
{
  float world_width = world->get_track()->width;
  float world_height = world->get_track()->height;
  scale = min((float)GAME_WIDTH / world_width, (float)HEIGHT / world_height);

  // To enabling centering in the smaller (padded) axis
  extra_x = (GAME_WIDTH - scale * world_width) / 2;
  extra_y = (HEIGHT - scale * world_height) / 2;
}

View::~View()
{
  delete gui_view;

  SDL_DestroyTexture(car_texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void View::init()
{
  string title = "Smart Cars";

  window = run_safe<SDL_Window *>(SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN));

  renderer = run_safe<SDL_Renderer *>(SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED));

  gui_view = new GuiView(world, renderer);
  gui_view->init();

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  car_texture = load_texture(renderer, "car").texture;
}

void View::update()
{
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

  // Clear screen with above color
  SDL_RenderClear(renderer);

  draw_cars();

  draw_track();

  gui_view->render();

  // Render stuff on window
  SDL_RenderPresent(renderer);
}

void View::draw_track()
{
  SDL_SetRenderDrawColor(renderer, 50, 255, 50, SDL_ALPHA_OPAQUE);

  for (TrackSegment *segment : world->get_track()->get_segments())
  {
    auto points = segment->get_points();
    for (int i = 0; i < points.size() - 1; i++)
    {
      render_line(points[i], points[i + 1]);
    }
  }

  SDL_SetRenderDrawColor(renderer, 255, 50, 50, SDL_ALPHA_OPAQUE);

  auto goal_line = world->get_track()->get_goal_line();
  render_line(goal_line->start, goal_line->end);
}

void View::draw_cars()
{
  for (auto car : world->get_cars())
  {
    SDL_Rect source_rect = {0,
                            0,
                            TextureSizes::CAR_WIDTH,
                            TextureSizes::CAR_HEIGHT};

    SDL_Rect destination_rect = {GUI_WIDTH + (int)((car->get_x() - car->width / 2) * scale) + extra_x,
                                 HEIGHT - (int)((car->get_y() + car->length / 2) * scale) - extra_y,
                                 (int)(car->width * scale),
                                 (int)(car->length * scale)};

    SDL_RenderCopyEx(
        renderer,
        car_texture,
        &source_rect,
        &destination_rect,
        (double)(car->get_rot()),
        NULL,
        SDL_FLIP_NONE);
  }
}

void View::render_line(Point start, Point end)
{
  SDL_RenderDrawLine(
      renderer,
      GUI_WIDTH + (int)(start.x * scale) + extra_x,
      HEIGHT - (int)(start.y * scale) - extra_y,
      GUI_WIDTH + (int)(end.x * scale) + extra_x,
      HEIGHT - (int)(end.y * scale) - extra_y);
}
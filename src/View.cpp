#define _USE_MATH_DEFINES
#include <math.h>

#include "view.h"
#include "SDL_utils.h"
#include "car.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
using namespace SDL_utils;

View::View(World *world) : world(world)
{
  float world_width = world->get_track()->get_width();
  float world_height = world->get_track()->get_height();
  scale = min((float)GAME_WIDTH / world_width, (float)HEIGHT / world_height);

  // To enabling centering in the smaller (padded) axis
  extra_x = (GAME_WIDTH - scale * world_width) / 2;
  extra_y = (HEIGHT - scale * world_height) / 2;
}

View::~View()
{
  delete gui_view;
  delete debug_view;

  SDL_DestroyTexture(car_texture.texture);
  SDL_DestroyTexture(wheel_texture.texture);
  SDL_DestroyTexture(goal_line_texture.texture);
  SDL_DestroyTexture(track_segment_texture.texture);

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

  debug_view = new DebugView(renderer, scale);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  car_texture = load_texture(renderer, "car");
  wheel_texture = load_texture(renderer, "wheel");
  goal_line_texture = load_texture(renderer, "goal_line");
  track_segment_texture = load_texture(renderer, "track_segment");
}

void View::update(int fps, function<void()> draw_debug)
{
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

  // Clear screen with above color
  SDL_RenderClear(renderer);

  /*draw_track();

  draw_cars();

  gui_view->render(fps);*/

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  draw_debug();

  // Render stuff on window
  SDL_RenderPresent(renderer);
}

DebugView *View::get_debug_view()
{
  return debug_view;
}

void View::draw_track()
{
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

  for (TrackSegment *segment : world->get_track()->get_segments())
  {
    auto points = segment->get_points();
    for (int i = 0; i < points.size() - 1; i++)
    {
      render_line(points[i], points[i + 1], track_segment_texture);
    }
  }

  auto goal_line = world->get_track()->get_goal_line();
  render_line(goal_line->start, goal_line->end, goal_line_texture);
}

void View::draw_cars()
{
  for (auto car : world->get_cars())
  {
    render_dynamic_body(car, car_texture.texture, false);

    auto wheels = car->get_wheels();
    for (int i = 0; i < wheels.size(); i++)
    {
      auto wheel = wheels[i];
      bool flip = i == Car::WheelPos::FRONT_RIGHT || i == Car::WheelPos::REAR_RIGHT;
      render_dynamic_body(wheel, wheel_texture.texture, flip);
    }
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

void View::render_line(Point start, Point end, TextureWrapper texture)
{
  float pixel_line_length = end.get_distance(start) * scale;
  float line_heading = end.get_heading(start);

  for (int total_height = 0; total_height < pixel_line_length; total_height += texture.height)
  {
    // Calculate x + y UNROTATED with heading = 0
    int next_height = min(texture.height, (int)(pixel_line_length - total_height));
    float start_x = end.x * scale;
    float start_y = end.y * scale;
    float y = total_height + next_height;

    SDL_Rect source_rect = {0, (texture.height - next_height), texture.width, next_height};

    // Apply rotations to x and y
    SDL_Rect destination_rect = {
        (int)(GUI_WIDTH + start_x + y * sin(line_heading) + extra_x),
        (int)(HEIGHT - (start_y + y * cos(line_heading)) - extra_y),
        texture.width,
        next_height};

    SDL_Point rotation_point = {0, 0};

    SDL_RenderCopyEx(
        renderer,
        texture.texture,
        &source_rect,
        &destination_rect,
        (double)(line_heading * 180 / M_PI),
        &rotation_point,
        SDL_FLIP_NONE);
  }
}

void View::render_dynamic_body(DynamicBody *body, SDL_Texture *texture, bool flip)
{
  SDL_Rect destination_rect = {GUI_WIDTH + (int)((body->get_x() - body->width / 2) * scale) + extra_x,
                               HEIGHT - (int)((body->get_y() + body->length / 2) * scale) - extra_y,
                               (int)(body->width * scale),
                               (int)(body->length * scale)};

  SDL_RenderCopyEx(
      renderer,
      texture,
      NULL,
      &destination_rect,
      (double)(body->get_rot()),
      NULL,
      flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
#include "gui_view.h"

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

void GuiView::render()
{
  text_renderer->render_text("Hi there", 10, 10);
}
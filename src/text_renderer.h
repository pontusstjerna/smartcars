#ifndef TEXT_RENDERER
#define TEXT_RENDERER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextRenderer
{
public:
  TextRenderer(SDL_Renderer *renderer);
  ~TextRenderer();

  void init();
  void render_text(std::string text, int x, int y);
  void render_bold_text(std::string text, int x, int y);
  void render_small_text(std::string text, int x, int y);

private:
  SDL_Renderer *renderer;
  TTF_Font *regular_font;
  TTF_Font *bold_font;
  TTF_Font *small_regular_font;

  void render_text(std::string text, TTF_Font *font, int x, int y);
};

#endif /* TEXT_RENDERER */

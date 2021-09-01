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
  void render_text(std::string, int x, int y);

private:
  SDL_Renderer *renderer;
  TTF_Font *regular_font;
  TTF_Font *bold_font;
};

#endif /* TEXT_RENDERER */

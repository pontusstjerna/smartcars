#include "text_renderer.h"
#include "SDL_utils.h"

using namespace std;
using namespace SDL_utils;

TextRenderer::TextRenderer(SDL_Renderer *renderer) : renderer(renderer)
{
}

TextRenderer::~TextRenderer()
{
  TTF_CloseFont(regular_font);
  TTF_CloseFont(bold_font);
}

void TextRenderer::init()
{
  SDL_utils::run_safe(TTF_Init());
  regular_font = SDL_utils::run_safe<TTF_Font *>(TTF_OpenFont("assets/fonts/Play-Regular.ttf", 28));
  bold_font = SDL_utils::run_safe<TTF_Font *>(TTF_OpenFont("assets/fonts/Play-Bold.ttf", 28));
  small_regular_font = SDL_utils::run_safe<TTF_Font *>(TTF_OpenFont("assets/fonts/Play-Regular.ttf", 16));
}

void TextRenderer::render_text(std::string text, int x, int y) { render_text(text, regular_font, x, y); }
void TextRenderer::render_bold_text(std::string text, int x, int y) { render_text(text, bold_font, x, y); }
void TextRenderer::render_small_text(std::string text, int x, int y) { render_text(text, small_regular_font, x, y); }

// Note! Highly inefficient to reload texture every frame. Consider changing method.
void TextRenderer::render_text(std::string text, TTF_Font *font, int x, int y)
{
  SDL_Color text_color = {255, 255, 255};
  TextureWrapper text_texture_wrapper = load_text_texture(renderer, text, text_color, font);

  SDL_Rect dest_rect = {x, y, text_texture_wrapper.width, text_texture_wrapper.height};
  SDL_RenderCopy(renderer, text_texture_wrapper.texture, NULL, &dest_rect);

  SDL_DestroyTexture(text_texture_wrapper.texture);
}
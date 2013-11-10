#pragma once
#include "Utils.h"

/**
 * The Purpose of this class is to ease the pains of rendering with SDL
 * and to keep from rendering things more than once.
 */
class RenderHelper
{
public:
    RenderHelper(SDL_Renderer* current_renderer, SDL_Window* current_window);
    ~RenderHelper();

    TTF_Font* LoadFont(std::string font_location, int font_size);
    SDL_Texture* LoadText(std::string text, std::string font_location, int font_size, SDL_Color font_color );
    SDL_Texture* LoadText( std::string text, TTF_Font* font, SDL_Color font_color );
    SDL_Texture* LoadTextDefaultFont( std::string text, SDL_Color font_color = ColorWhite, int font_size = DEFAULT_FONT_SIZE );
    SDL_Texture* LoadImage(std::string image_location);

    void GetFontSize(TTF_Font* font, std::string text, int *width, int *height);
    void GetTextureSize(SDL_Texture* texture, int *width, int *height);
    void GetWindowSize( int *width, int *height );
    void GetCenterForTexture(SDL_Texture* texture, int *x, int *y);
    void RenderTextureScale(SDL_Texture* texture);
    void RenderTextureAutoSize(SDL_Texture* texture, SDL_Rect* destination, SDL_Rect* source);
    void RenderTexture(SDL_Texture* text_texture, SDL_Rect* destination, SDL_Rect* source = nullptr);

private:
    GameLog *m_cLogger;
    SDL_Renderer* m_cLoadedRenderer;
    SDL_Window* m_cLoadedWindow;
};

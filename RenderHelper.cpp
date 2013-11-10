#include "RenderHelper.h"


RenderHelper::RenderHelper(SDL_Renderer* current_renderer, SDL_Window* current_window)
{
    m_cLoadedRenderer = current_renderer;
    m_cLoadedWindow = current_window;
    m_cLogger = new GameLog("RenderHelper");
}
   
RenderHelper::~RenderHelper()
{
    SAFE_DELETE(m_cLogger);
    // How do we release pointer we dont own
}


/**
* Get the size of the current window
* @param width  a pointer to be filled with the width of the current window
* @param height a pointer to be filled with the height of the current window
*/
void RenderHelper::GetWindowSize( int *width, int *height )
{
    SDL_GetWindowSize( m_cLoadedWindow, width, height);
}

/**
* Load a texture filled with text using SDL_ttf
* @param  font_location the location of the font file to be used
* @param  font_size     the size of the font in pixels
* @param  text          the text to be printed with the font
* @param  font_color    The Color to make the font
* @return               The texture object containing the font
*/
SDL_Texture* RenderHelper::LoadText(std::string text, std::string font_location, int font_size, SDL_Color font_color)
{
    m_cLogger->Log("Attempting to Load Text: " + text);
    TTF_Font* font = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Texture *texture = nullptr;

    font = LoadFont(font_location, font_size);
    if( font == nullptr )
    {
        return nullptr;
    }

    return LoadText(text, font, font_color);
}

SDL_Texture* RenderHelper::LoadText( std::string text, TTF_Font* font, SDL_Color font_color )
{
    SDL_Surface* surface = nullptr;
    SDL_Texture *texture = nullptr;
    surface = TTF_RenderText_Blended(font, text.c_str(), font_color);
    if( surface == nullptr )
    {
        m_cLogger->LogSdlError("TTF_RenderText_Solid/LoadText");
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(m_cLoadedRenderer,surface);
        if( texture == nullptr )
        {
            m_cLogger->LogSdlError("SDL_CreateTextureFromSurface/LoadText");
        }
    }

    TTF_CloseFont(font);
    font = nullptr;
    SDL_FreeSurface(surface);
    surface = nullptr;

    return texture;
}

/**
* Load an image file into a texture
* @param  image_location The location of the image to load into a texture
* @return                Return a texture object containing the image
*/
SDL_Texture* RenderHelper::LoadImage(std::string image_location)
{
    m_cLogger->Log("Attempting to load file: " + image_location);
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture( m_cLoadedRenderer, image_location.c_str() );
    if( texture == nullptr )
    {
        m_cLogger->LogSdlError("IMG_LoadTexture/LoadImage");
    }
    else
    {
        m_cLogger->Log("Successfully loaded image");
    }

    return texture;
}

/**
* Load a font file into an SDL_font object
* @param  font_location the location of the font
* @param  font_size     the size of the fonts text
* @return font          an SDL object containing the font
*/
TTF_Font* RenderHelper::LoadFont(std::string font_location, int font_size)
{
    m_cLogger->Log("Attempting to Load Font: " + font_location);

    TTF_Font* font = nullptr;
    font = TTF_OpenFont(font_location.c_str(), font_size);
    if( font == nullptr )
    {
        m_cLogger->LogSdlError("TTF_OpenFont/LoadText");
    }
    else
    {
        m_cLogger->Log("Font successfully Loaded");
    }

    return font;
}

/**
* Get the size of a texture
* @param texture the texture to find the width an height of
* @param width   a pointer to be filled with the width of a texture
* @param height  a pointer to be filed with the height of a texture
*/
void RenderHelper::GetTextureSize(SDL_Texture* texture, int *width, int *height)
{
    SDL_QueryTexture(texture, NULL, NULL, width, height);
}

/**
* This function gets the height and width of a specific font with text
* @param  font   An SDL font object
* @param  text   the text that will probably be going into that object
* @param  width  a pointer to be filled with that fonts width
* @param  height a pointer to be filled with that fonts height
*/
void RenderHelper::GetFontSize(TTF_Font* font, std::string text, int *width, int *height)
{
    TTF_SizeText(font, text.c_str(), width, height);
}

void RenderHelper::GetCenterForTexture(SDL_Texture* texture, int *x, int *y)
{
    int texture_width, texture_height;
    GetTextureSize(texture, &texture_width, &texture_height);

    int screen_width, screen_height;
    GetWindowSize(&screen_width, &screen_height);

    if( x )
    {
        *x = (screen_width/2) - (texture_width/2);
    }

    if( y )
    {
        *y = (screen_height/2) - (texture_height/2);
    }
}
/**
* Render a texture and scale it to the screen size
* @param texture the texture to render at screen size
*/
void RenderHelper::RenderTextureScale(SDL_Texture* texture)
{
    int screen_width = 0;
    int screen_height = 0;

    GetWindowSize( &screen_width, &screen_height );

    int texture_height = 0;
    int texture_width = 0;
    GetTextureSize(texture, &texture_width, &texture_height);

    SDL_Rect source;
    SDL_Rect destination;

    source.x = 0;
    source.y = 0;
    source.h = texture_height;
    source.w = texture_width;

    destination.x = 0;
    destination.y = 0;
    destination.h = screen_height;
    destination.w = screen_width;

    SDL_RenderCopy(m_cLoadedRenderer, texture, &source, &destination);
}

/**
* Render a texture that has already been loaded
* @param text_texture the texture to render
* @param destination  the destination of that texture
*/
void RenderHelper::RenderTexture(SDL_Texture* texture, SDL_Rect* destination, SDL_Rect* source)
{
    SDL_RenderCopy(m_cLoadedRenderer, texture, source, destination);
}

SDL_Texture* RenderHelper::LoadTextDefaultFont( std::string text, SDL_Color font_color /*= ColorWhite*/, int font_size /*= DEFAULT_FONT_SIZE*/ )
{
    return LoadText(text, DEFAULT_FONT, font_size, font_color);
}

/**
* Render a texture that has already been loaded
* @param text_texture the texture to render
* @param destination  the destination of that texture
*/
void RenderHelper::RenderTextureAutoSize(SDL_Texture* texture, SDL_Rect* destination, SDL_Rect* source)
{
    GetTextureSize(texture, &destination->w, &destination->h);
    RenderTexture(texture, destination, source);
}

#include "SpriteSheet.h"

/**
* Load a Sprite Sheet into memory
* @param spritesheet_source    location of the sprite sheet relative to this file
* @param sprite_height         the height of one sprite
* @param sprite_width          the width of one sprite
* @param render_helper         The Render Helper to render with
*/
SpriteSheet::SpriteSheet(std::string spritesheet_source, int sprite_height, int sprite_width, RenderHelper* render_helper, int margin, int spacing)
{
    int last_slash = spritesheet_source.find_last_of("/");
    m_cRenderHelper = render_helper;
    if( last_slash > 0 )
    {
        spritesheet_source = spritesheet_source.substr(last_slash+1);
    }
    spritesheet_source = SPRITE_FOLDER + spritesheet_source;

    m_cTexture = m_cRenderHelper->LoadImage(spritesheet_source);
    m_iSpriteHeight = sprite_height;
    m_iSpriteWidth = sprite_width;
    m_iSpacing = spacing;
    m_iMargin = margin;
    m_cRenderHelper->GetTextureSize(m_cTexture, &m_iTotalWidth, &m_iTotalHeight);
}

/**
* Cleanup and Zero out all of our Sprite Sheet Variables
*/
SpriteSheet::~SpriteSheet()
{
    SDL_DestroyTexture(m_cTexture);
    m_cTexture     = nullptr;
    m_iSpriteHeight  = 0;
    m_iSpriteWidth   = 0;
    m_iTotalWidth  = 0;
    m_iTotalHeight = 0;
    m_iSpacing = 0;
    m_iMargin = 0;
}

/**
* Round a value up by a multiple
*/
int SpriteSheet::RoundUp(int number, int multiple)
{
    if(multiple == 0)
    {
        return number;
    }

    if(number < 0)
    {
        multiple = -multiple;
    }

    int remainder = number % multiple;

    if(remainder == 0)
    {
        return number;
    }

    return (number + multiple - remainder);
}

/**
* Get the x and y position of a tile on a sprite sheet
* @param sprite_id the id of the tile, from left to right
* @param sprite_x  the variable to fill with the tiles sprite sheet x coordinate
* @param sprite_y  the variable to fill with the tiles sprite sheet y coordinate
*/
void SpriteSheet::GetSpritePosition(int sprite_id, int *sprite_x, int *sprite_y)
{
    int sprites_per_row = m_iTotalWidth/m_iSpriteWidth;
    int column_for_id = sprite_id/sprites_per_row;

    // round_up can be found in Utils
    column_for_id = RoundUp(column_for_id, 1);

    *sprite_x = ((sprite_id * m_iSpriteWidth) + m_iSpacing)  + (m_iMargin*sprite_id);
    *sprite_y = ((column_for_id * m_iTotalHeight) + m_iSpacing) + (m_iMargin*column_for_id);
}

/**
* Draw a tile given an id and the location to render to
* @param current_renderer the current rendering target
* @param sprite_id        the id of the sprite to render
* @param x                the x coordinate where the tile should render
* @param y                the y coordinate where the tile should render
*/
void SpriteSheet::DrawTile(int sprite_id, int x, int y)
{
    SDL_Rect source;
    SDL_Rect destination;

    source.h = m_iSpriteHeight;
    source.w = m_iSpriteWidth;
    GetSpritePosition(sprite_id, &source.x, &source.y);

    destination.x = x * m_iSpriteWidth;
    destination.y = y * m_iSpriteHeight;
    destination.h = source.h;
    destination.w = source.w;

    m_cRenderHelper->RenderTexture(m_cTexture, &destination, &source);
}

void SpriteSheet::SetProperty( std::string name, std::string value )
{
    m_hssProperties[name] = value;
}

std::string SpriteSheet::SearchPropertyName( std::string name )
{
    std::hash_map< std::string, std::string>::iterator it = m_hssProperties.find(name);

    std::string value;
    if( it != m_hssProperties.end() )
    {
        value = it->second;
    }

    return value;

}

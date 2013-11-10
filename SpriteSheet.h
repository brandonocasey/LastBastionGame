#pragma once
#include "Utils.h"
#include "RenderHelper.h"
#include "SetupHelper.h"

class SpriteSheet
{
public:
    SpriteSheet(std::string spritesheet_source, int sprite_height, int sprite_width, RenderHelper* render_helper, int margin = 0, int spacing = 0);
    ~SpriteSheet();
    void GetSpritePosition(int sprite_id, int *sprite_x, int *sprite_y);
    void DrawTile(int sprite_id, int x, int y);
    int RoundUp(int number, int multiple);
    void SetProperty( std::string name, std::string value );
    std::string SearchPropertyName( std::string name );
private:
    int m_iSpriteHeight;
    int m_iSpriteWidth;
    int m_iTotalWidth;
    int m_iTotalHeight;
    int m_iSpacing;
    int m_iMargin;
    SDL_Texture* m_cTexture;
    RenderHelper* m_cRenderHelper;
    SetupHelper* m_cSetupHelper;
    std::hash_map< std::string, std::string> m_hssProperties;
};

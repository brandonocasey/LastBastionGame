#pragma once
#include "BaseGameState.h"
#include "RenderHelper.h"
#include "SpriteSheet.h"

class GamePlayState : public BaseGameState
{
public:
    void LoadMap()
    {
        for (int i = 0; i < m_cMap->GetNumTilesets(); ++i)
        {
            // Get a tileset.
            const Tmx::Tileset *tileset = m_cMap->GetTileset(i);

            std::string tileset_source = tileset->GetImage()->GetSource();
            if( !tileset_source.empty() )
            {
                m_hTileSet[i] = new SpriteSheet(tileset_source, tileset->GetTileWidth(), tileset->GetTileHeight(), m_cRenderHelper, tileset->GetMargin(), tileset->GetSpacing());
            }
        }
    }
    void LoadMapCollision()
    {
        for (int i = 0; i < m_cMap->GetNumLayers(); ++i)
        {
            const Tmx::Layer *layer = m_cMap->GetLayer(i);
            if( layer->GetName() == "Meta")
            {
                m_vviCollision.resize(layer->GetHeight());
                for (int y = 0; y < layer->GetHeight(); ++y)
                {
                    m_vviCollision[y].resize(layer->GetHeight());
                    for (int x = 0; x < layer->GetWidth(); ++x)
                    {
                        int tileset_id = layer->GetTile(x,y).tilesetId;
                        if( tileset_id != -1 )
                        {
                            const Tmx::Tileset *tileset = m_cMap->GetTileset(tileset_id);
                            std::vector<Tmx::Tile*> tiles = tileset->GetTiles();

                            Tmx::PropertySet properties = tiles[layer->GetTileId(x, y)]->GetProperties();

                            std::string collision = properties.GetLiteralProperty("collision");
                            std::string waypoint = properties.GetLiteralProperty("waypoint");
                            std::string health = properties.GetLiteralProperty("health");
                            if( collision == "true" )
                            {
                                m_vviCollision[y][x] = 1;
                            }
                            else
                            {
                                m_vviCollision[y][x] = 0; 
                            }
                        }
                    }
                }
            }
        }
    }

    void Init(SDL_Renderer* current_renderer, SDL_Window* current_window)
    {
        m_cRenderHelper = new RenderHelper(current_renderer, current_window);
        std::string map_location = "Assets/maps/level1.tmx";
        m_cRenderHelper = new RenderHelper(current_renderer, current_window);
        m_cLogger->Log("Attempting to parse map located at " + map_location);
        m_cMap->ParseFile(map_location);

        // Resize collsion vector to map size

        if (m_cMap->HasError())
        {
            m_cLogger->LogError("error code: " +  m_cMap->GetErrorCode());
            m_cLogger->LogError("error text: " +  m_cMap->GetErrorText());
        }
        else
        {
            m_cLogger->Log("Successfully loaded map located at " + map_location);
        }

        LoadMap();
        LoadMapCollision();
    }
    void Update();
    void Draw();
    void HandleEvents();
    void PauseState();
    void ResumeState();
    GamePlayState();
    ~GamePlayState();

private:
    RenderHelper *m_cRenderHelper;
    Tmx::Map* m_cMap;
    std::hash_map<int, SpriteSheet*> m_hTileSet;
    std::vector< std::vector<int> > m_vviCollision;
};

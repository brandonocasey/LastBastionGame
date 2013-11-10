#include "GamePlayState.h"

void GamePlayState::Update()
{

}

void GamePlayState::Draw()
{
    for (int i = 0; i < m_cMap->GetNumLayers(); ++i)
    {
        const Tmx::Layer *layer = m_cMap->GetLayer(i);

        if( layer->GetName() != "Meta" ) // Meta
        {
            for (int y = 0; y < layer->GetHeight(); ++y)
            {
                for (int x = 0; x < layer->GetWidth(); ++x)
                {
                    int tileset_id = layer->GetTile(x,y).tilesetId;
                    // Draw a tile
                    if( tileset_id != -1  ) // && m_vviCollision[y][x] == 1
                    {
                        m_hTileSet[tileset_id]->DrawTile(layer->GetTileId(x, y), x, y);
                    }
                }
            }
        }
    }
}

void GamePlayState::HandleEvents()
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {

        if( event.type == SDL_QUIT )
        {
            m_cLogger->Log("SDL_QUIT was found, YAY?! were not handling this now");
        }
    }
}

void GamePlayState::PauseState()
{

}

void GamePlayState::ResumeState()
{

}

GamePlayState::GamePlayState()
{
    m_sName = "GamePlayState";
    m_cLogger = new GameLog(m_sName.c_str());
    m_cMap = new Tmx::Map;
}

GamePlayState::~GamePlayState()
{

}
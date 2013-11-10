#include "GameEngine.h"

GameEngine::GameEngine()
{
    m_cLogger = new GameLog("GameEngine");
    m_bRunning = true;
    m_cSetupHelper = SetupHelper::GetSetupHelper();
}

GameEngine::~GameEngine()
{
    m_bRunning = false;
    m_cLogger->Log("Cleaning up the game");
    // Clear out all of our elements, automatically deconstructed as well.
    m_vStateStack.clear();
    SAFE_DELETE(m_cSetupHelper);
    SAFE_DELETE(m_cLogger);
}

bool GameEngine::Init()
{
    return m_cSetupHelper->InitSDL();
}

bool GameEngine::InitVideo( const char* title, int width /*= 640*/, int height /*= 640*/, bool fullscreen /*= false*/ )
{
    return m_cSetupHelper->InitVideo(title, width, height, fullscreen);
}

bool GameEngine::InitAudio( int channels /*= 2*/, int chunksize /*= 4096*/, int frequency /*= 22050*/ )
{
    return m_cSetupHelper->InitAudio(channels, chunksize, frequency);
}

bool GameEngine::InitNetwork()
{
    return m_cSetupHelper->InitNetwork();
}

bool GameEngine::InitControls()
{
    return m_cSetupHelper->InitControls();
}

bool GameEngine::ParseCommandLine( int argc, char * argv[] )
{
    return m_cSetupHelper->ParseCommandLine(argc, argv);
}

void GameEngine::ChangeState( BaseGameState* state )
{
    m_vStateStack.push_back(state);
    //
    m_vStateStack.back().Init(m_cSetupHelper->GetRenderer(), m_cSetupHelper->GetWindow());
    m_cLogger->Log("Changing state to " +  m_vStateStack.back().GetName());

}

void GameEngine::PauseState()
{

}

void GameEngine::ResumeState()
{

}

void GameEngine::PopState()
{

}

void GameEngine::PushState()
{

}

bool GameEngine::Running()
{
    return m_bRunning;
}

void GameEngine::Run()
{
    m_cSetupHelper->ClearRenderer();
    HandleEvents();
    Update();
    Draw();
    m_cSetupHelper->PresentRenderer();
}

void GameEngine::Draw()
{
    m_vStateStack.back().Draw();
}

void GameEngine::HandleEvents()
{
    m_vStateStack.back().HandleEvents();
}

void GameEngine::Update()
{
    m_vStateStack.back().Update();
}

void GameEngine::Quit()
{
    m_cLogger->Log("Quit has been called.");
    m_bRunning = false;
}
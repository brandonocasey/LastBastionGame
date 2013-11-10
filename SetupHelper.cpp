#include "SetupHelper.h"

SetupHelper SetupHelper::m_SetupHelper;


SetupHelper::SetupHelper()
{
    m_cLogger = new GameLog("SetupHelper");
    /*
    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> m_cWindow 
        = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> m_cRenderer
        = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
        */
}

SetupHelper::~SetupHelper()
{
    SDL_DestroyWindow(m_cWindow);
    SDL_DestroyRenderer(m_cRenderer);
    SAFE_DELETE(m_cLogger);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool SetupHelper::InitSDL()
{
    // Initialize our SDL Session
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        m_cLogger->LogSdlError( "SDL_Init: " );
        return false;
    }
    else
    {
        m_cLogger->Log("SDL_Init: SDL_Init_Everything work OK");
    }
    return true;
}

bool SetupHelper::InitAudio( int channels, int chunksize, int frequency )
{
    //m_iSoundVolume = MIX_MAX_VOLUME;
    //m_iAllVolume = MIX_MAX_VOLUME;
    if( Mix_OpenAudio( frequency, MIX_DEFAULT_FORMAT, channels, chunksize ) == -1 )
    {
        m_cLogger->LogSdlError( "Mix_OpenAudio" );
        return false;
    }
    else
    {
        m_cLogger->Log("Mix_OpenAudio was Successfully!");
    }

    return true;
}

bool SetupHelper::InitVideo( const char* title, int width, int height, bool fullscreen )
{
    // Create Our Window
    // m_cWindow.reset();
    m_cWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if( m_cWindow == nullptr )
    {
        m_cLogger->LogSdlError("SDL_CreateWindow");
        return false;
    }
    else
    {
        m_cLogger->Log("SDL_CreateWindow was successful");
    }

    m_cRenderer = SDL_CreateRenderer(m_cWindow, -1, SDL_RENDERER_ACCELERATED );

    if (m_cRenderer == nullptr)
    {
        m_cLogger->LogSdlError("SDL_CreateRenderer");
        return false;
    }
    else
    {
        m_cLogger->Log("Render Successfully Created!");
    }


    int img_flags = IMG_INIT_JPG|IMG_INIT_PNG;
    if ((IMG_Init(img_flags) != img_flags))
    {
        m_cLogger->LogSdlError("IMG_Init");
        return false;
    }
    else
    {
        m_cLogger->Log("IMG_Init was successful!");
    }

    if (TTF_Init() == -1)
    {
        m_cLogger->LogSdlError("TTF_Init");
        return false;
    }
    else
    {
        m_cLogger->Log("TTF_Init was successful!");
    }

    if( SDL_SetRenderDrawColor(m_cRenderer, 0, 0, 0, 255) == -1)
    {
        m_cLogger->LogSdlError("SDL_SetRenderDrawColor");
    }
    else
    {
        m_cLogger->Log("SDL_SetRenderDrawColor color set to black");
    }

    ClearRenderer();

    if( fullscreen )
    {
        FullScreenOn();
    }
    else
    {
        FullScreenOff();
    }
    return true;
}

bool SetupHelper::InitNetwork()
{
    m_cLogger->Log("Init Network called but NYI");
    return true;
}

bool SetupHelper::InitControls()
{
    m_cLogger->Log("Init Controls called but NYI");

    SDL_ShowCursor(1);

    // We should probably choose a control scheme here
    return true;
}

bool SetupHelper::ParseCommandLine(int argc, char * argv[])
{
    m_cLogger->Log("Parse Command Line called but NYI");
    return true;
}


void SetupHelper::ClearRenderer()
{
    SDL_RenderClear(m_cRenderer);
}

void SetupHelper::PresentRenderer()
{
    SDL_RenderPresent(m_cRenderer);
}

/**
* Turn Fullscreen on and save previous screen size.
*/
void SetupHelper::FullScreenOn()
{
    GetWindowSize(&m_iPreviousWindowWidth, &m_iPreviousWindowHeight);
    // We store this so that if they toggle back out of fullscreen
    // We can resize the window from the crazy resolution that the window
    // will end up as
    if( SDL_SetWindowFullscreen(m_cWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) == 0 )
    {
        m_cLogger->Log("Fullscreen successfully initialized");
    }
    else
    {
        m_cLogger->LogSdlError("SDL_SetWindowFullscreen on");
    }
}


/**
* Turn fullscreen off and restore previous screen size if it exists
*/
void SetupHelper::FullScreenOff()
{
    if( SDL_SetWindowFullscreen(m_cWindow, SDL_FALSE) == 0 )
    {
        m_cLogger->Log("Fullscreen successfully turned off");
    }
    else
    {
        m_cLogger->LogSdlError("SDL_SetWindowFullscreen off");
    }

    // Window is really big after fullscreen turns of if we don't do this.
    if( m_iPreviousWindowWidth && m_iPreviousWindowWidth )
    {
        ChangeWindowSize(m_iPreviousWindowWidth, m_iPreviousWindowHeight);
    }
}


/**
* Resize the game window, for use with the setting menu. Also saves previous window size
* For things that need to revert the window size
* @param width  width of the screen
* @param height height of the screen
*/
void SetupHelper::ChangeWindowSize(int width, int height)
{
    m_cLogger->Log("Resizing window to h = " + std::to_string(height) + " w = " + std::to_string(width));
    SDL_SetWindowSize(m_cWindow, width, height);
    m_iWindowWidth = width;
    m_iWindowHeight = height;
}

SDL_Window* SetupHelper::GetWindow()
{
    return m_cWindow;
}

SDL_Renderer* SetupHelper::GetRenderer()
{
    return m_cRenderer;
}

/**
* Get the size of the current window
* @param width  a pointer to be filled with the width of the current window
* @param height a pointer to be filled with the height of the current window
*/
void SetupHelper::GetWindowSize( int *width, int *height )
{
    SDL_GetWindowSize(m_cWindow, width, height);

    //logger.Log("Current window is h = " + std::to_string(*height) + " w = " + std::to_string(*width));
}
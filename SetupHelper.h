#pragma once;
#include "Utils.h"

class SetupHelper
{
public:
    ~SetupHelper();
    SetupHelper();
    
    bool InitSDL();
    bool InitAudio(int channels, int chunksize, int frequency);
    bool InitVideo(const char* title, int width, int height, bool fullscreen);
    bool InitNetwork();
    bool InitControls();
    bool ParseCommandLine(int argc, char * argv[]);
    static SetupHelper* GetSetupHelper()
    {
        return &m_SetupHelper;
    }

    void GetWindowSize( int *width, int *height );
    void ClearRenderer();
    void PresentRenderer();
    void FullScreenOn();
    void FullScreenOff();
    void ChangeWindowSize(int width, int height);


    SDL_Window* GetWindow();
    SDL_Renderer* GetRenderer();
private:
    static SetupHelper m_SetupHelper;
    //static std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> m_cWindow;
    //static std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> m_cRenderer;
    SDL_Window* m_cWindow;
    SDL_Renderer *m_cRenderer;

    int m_iWindowHeight;
    int m_iWindowWidth;
    int m_iPreviousWindowWidth;
    int m_iPreviousWindowHeight;

    GameLog *m_cLogger;
};

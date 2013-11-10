#include "Utils.h"
#include "BaseGameState.h"
#include "SetupHelper.h"

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    bool InitVideo(const char* title, int width = 640, int height = 640, bool fullscreen = false);
    bool InitAudio(int channels = 2, int chunksize = 4096, int frequency = 22050);
    bool InitNetwork();
    bool Init();
    bool InitControls();
    bool ParseCommandLine(int argc, char * argv[]);

    void GetWindow();
    void GetRenderer();
    void ChangeState(BaseGameState* state);
    void PauseState();
    void ResumeState();
    void PopState();
    void PushState();

    bool Running();
    void Run();
    void Draw();
    void HandleEvents();
    void Update();
    void Quit();

private:
    boost::ptr_vector<BaseGameState> m_vStateStack;
    bool m_bRunning;
    GameLog* m_cLogger;
    SetupHelper* m_cSetupHelper;
};

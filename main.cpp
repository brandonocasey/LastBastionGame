#include "Utils.h"
#include "GameEngine.h"
#include "GamePlayState.h"

int main(int argc, char * argv[])
{
    GameEngine *game = new GameEngine();

    // Parse things passed in from command line
    if( !game->ParseCommandLine(argc, argv) )
    {
        return 1;
    }

    // Start SDL
    if( !game->Init() )
    {
        return 2;
    }

    if( !game->InitVideo(GAME_NAME) )
    {
        return 3;
    }

    // Start our Audio Engine
    if( !game->InitAudio() )
    {
        return 4;
    }

    if( !game->InitNetwork() )
    {
        return 5;
    }

    // Start SDL
    if( !game->InitControls() )
    {
        return 6;
    }

    game->ChangeState( new GamePlayState() );

    while( game->Running() )
    {
        game->Run();
    }


    return 0;
}
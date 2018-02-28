#include "game.h"

int main(int argc, char const *argv[])
{
    Game game;
    while(!game.GetWindow()->IsDone())
    {
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock();
    }
    return 0;
}

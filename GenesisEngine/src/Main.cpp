#include <iostream>
#include "Game.h"
#include "Constants.h"
#include <sol/sol.hpp>//binding of Lua and cpp.

int main(int argc, char* argv[])
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    Game* game = new Game();

    game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->IsRunning())
    {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    game->Destroy();
    delete game;

    return 0;
}

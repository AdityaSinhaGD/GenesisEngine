#include <iostream>
#include "Game.h"
#include "Constants.h"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "Hello, world!" << std::endl;

    Game* game = new Game();

    game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game->IsRunning())
    {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    game->Destroy();

    return 0;
}

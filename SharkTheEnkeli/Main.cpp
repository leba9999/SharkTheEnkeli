#include "Game.h"

Console* Console::pinstance_{nullptr};
std::mutex Console::mutex_;

int main(int argc, char* argv[])
{
    Game* game = new Game(argc, argv);
    game->run();
    return 0;
}
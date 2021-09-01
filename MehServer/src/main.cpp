//SELF
#include "MehServer/Game.hpp"

//LIBS

//STD

int main(int, char*[])
{
    //todo: CLI for the server, and an optional CLI flag for an IMGUI window
    //maybe consider launching the window by default
    meh::server::Game game;
    return game.run();
}
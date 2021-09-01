//SELF
#include "MehServer/Game.hpp"

//LIBS
#include <doctest/doctest.h>

//STD

TEST_CASE("test")
{
    CHECK_EQ(meh::server::Game::add(1, 2), 3);
}
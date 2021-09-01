//SELF
#include "MehClient/Game.hpp"

//LIBS
#include <doctest/doctest.h>

//STD

TEST_CASE("test")
{
    CHECK_EQ(meh::client::Game::add(1, 2), 3);
}
//SELF
#include "CommonLib/Window/WindowNone.hpp"

//LIBS
#include <doctest/doctest.h>

//STD

TEST_CASE("test")
{
    meh::common::WindowNone window({});
    REQUIRE(window.isOpen());
    window.close();
    REQUIRE(!window.isOpen());
}
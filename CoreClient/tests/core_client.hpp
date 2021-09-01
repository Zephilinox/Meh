//SELF
#include "CoreClient/Library.hpp"

//LIBS
#include <doctest/doctest.h>

//STD

TEST_CASE("test")
{
    core::client::Library lib;
    CHECK(lib.doThing());
}
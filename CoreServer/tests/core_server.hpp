//SELF
#include "CoreServer/Library.hpp"

//LIBS
#include <doctest/doctest.h>

//STD

TEST_CASE("test")
{
    core::server::Library lib;
    CHECK(lib.doThing());
}
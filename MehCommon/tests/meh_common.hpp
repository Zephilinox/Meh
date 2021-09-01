//SELF
#include "MehCommon/Library.hpp"

//LIBS
#include <doctest/doctest.h>

//STD

TEST_CASE("test")
{
    meh::common::Library lib;
    CHECK(lib.doThing());
}
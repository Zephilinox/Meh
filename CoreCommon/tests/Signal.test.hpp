//SELF
#include "CoreCommon/Signal/Signal.hpp"

//LIBS
#include <doctest/doctest.h>

//STD

struct MyClass
{
    MyClass(int* c)
        : count(c)
    {
    }

    void do_thing(int a)
    {
        CHECK(a == 5);
        (*count)++;
    }

    int* count;
};

TEST_CASE("Signal/Emit int")
{
    core::common::Signal<int> signal;
    unsigned int count = 0;

    signal.connect([&count](int a) {
        CHECK(a == 5);
        count++;
    });

    signal.emit(5);
    CHECK(count == 1);
}

TEST_CASE("Signal/Emit const int&")
{
    core::common::Signal<const int&> signal;
    unsigned int count = 0;

    signal.connect([&count](int a) {
        CHECK(a == 5);
        count++;
    });

    signal.emit(5);
    CHECK(count == 1);
}

TEST_CASE("Signal/Emit int&")
{
    core::common::Signal<int&> signal;
    int count = 0;

    signal.connect([](int& a) {
        CHECK(a == 0);
        a++;
    });

    signal.emit(count);
    CHECK(count == 1);
}

TEST_CASE("Signal/Emit member function")
{
    {
        core::common::Signal<int> signal;
        int count = 0;
        MyClass myclass(&count);

        signal.connect(&myclass, &MyClass::do_thing);

        signal.emit(5);
        CHECK(count == 1);
    }
}

TEST_CASE("Signal/Connection")
{
    core::common::Signal<int> signal;
    unsigned int count = 0;

    auto lambda = [&count](int a) {
        CHECK(a == 5);
        count++;
    };

    {
        // can connect and disconnect
        auto dc = signal.connect(lambda);
        CHECK(dc);

        CHECK(dc.disconnect());
        CHECK(!dc.disconnect());
        CHECK(!dc);
    }

    {
        // two can connect, disconnect, and be different while valid, and the same when invalid
        auto dc = signal.connect(lambda);
        auto dc2 = signal.connect(lambda);
        CHECK_NE(dc, dc2);
        CHECK(dc);
        CHECK(dc2);
        CHECK(dc.disconnect());
        CHECK(dc2.disconnect());
        CHECK(!dc);
        CHECK(!dc2);
        CHECK_EQ(dc, dc2);
    }

    {
        // one can connect and then move, and be different while valid, and the same when invalid
        auto dc = signal.connect(lambda);
        auto dc2 = std::move(dc);
        CHECK_NE(dc, dc2);
        CHECK(!dc);
        CHECK(!dc.disconnect());
        CHECK(dc2);
        CHECK(dc2.disconnect());
        CHECK(!dc2);
        CHECK_EQ(dc, dc2);
    }

    {
        // one can connect and then be copied, be the same while valid, and the same when invalid, and they can both disconnect safely
        auto dc3 = signal.connect(lambda);
        auto dc4 = dc3;
        CHECK(dc3);
        CHECK(dc4);
        CHECK_EQ(dc3, dc4);
        CHECK(dc3.disconnect());
        CHECK_NE(dc3, dc4);
        CHECK(!dc4.disconnect());
        CHECK_EQ(dc3, dc4);
    }

    // nothing is emitted
    signal.emit(0);
    signal.emit(0);
    signal.emit(0);
    CHECK(count == 0);
}

TEST_CASE("Signal/ManagedConnection")
{
    core::common::Signal<int> signal;
    unsigned int count = 0;

    auto lambda = [&count](int a) {
        CHECK(a == 5);
        count++;
    };

    {
        // can connect and disconnect
        core::common::ManagedConnection mc = signal.connect(lambda);
        CHECK(mc);

        CHECK(mc.disconnect());
        CHECK(!mc.disconnect());
        CHECK(!mc);

        signal.emit(0);
        CHECK(count == 0);
    }

    {
        // can connect and then disconnect via destruction
        auto mc = std::make_unique<core::common::ManagedConnection>(signal.connect(lambda));
        CHECK(*mc);

        mc.reset();

        signal.emit(0);
        CHECK(count == 0);
    }

    {
        // can copy
        core::common::ManagedConnection mc = signal.connect(lambda);
        auto mc2 = mc;
        CHECK(mc);
        CHECK(mc2);
        CHECK_EQ(mc, mc2);
        CHECK(mc.disconnect());
        CHECK(!mc.disconnect());
        CHECK(!mc);
        CHECK_NE(mc, mc2);
        CHECK(!mc2.disconnect());
        CHECK(!mc2.disconnect());
        CHECK(!mc2);
        CHECK_EQ(mc, mc2);

        signal.emit(0);
        CHECK(count == 0);
    }

    {
        // can move and manually disconnect
        core::common::ManagedConnection mc = signal.connect(lambda);
        auto mc2 = std::move(mc);
        CHECK(!mc);
        CHECK(mc2);
        CHECK_NE(mc, mc2);
        CHECK(!mc.disconnect());
        CHECK(!mc.disconnect());
        CHECK(!mc);
        CHECK_NE(mc, mc2);
        CHECK(mc2.disconnect());
        CHECK(!mc2.disconnect());
        CHECK(!mc2);
        CHECK_EQ(mc, mc2);

        signal.emit(0);
        CHECK(count == 0);
    }

    {
        // can move and automatically disconnect
        {
            core::common::ManagedConnection mc = signal.connect(lambda);
            auto mc2 = std::move(mc);
            CHECK(!mc);
            CHECK(mc2);
            CHECK_NE(mc, mc2);
            CHECK(!mc.disconnect());
            CHECK(!mc.disconnect());
            CHECK(!mc);
            CHECK_NE(mc, mc2);
        }

        signal.emit(0);
        CHECK(count == 0);
    }

    {
        // disconnects existing connection before taking on new connection. can be created from Connection
        {
            core::common::ManagedConnection mc = signal.connect(lambda);
            mc = signal.connect(lambda);
            mc = signal.connect(lambda);
            signal.emit(5);
            CHECK(count == 1);
        }

        count = 0;
        signal.emit(0);
        CHECK(count == 0);
    }

    signal.emit(0);
    signal.emit(0);
    signal.emit(0);
    CHECK(count == 0);
}

TEST_CASE("Signal/Destroyed while Connection held")
{
    core::common::Connection c;

    {
        core::common::Signal<int> signal;
        unsigned int count = 0;

        c = signal.connect([&count](int a) {
            CHECK(a == 5);
            count++;
        });

        signal.emit(5);
        CHECK(count == 1);
    }

    CHECK(!c);
    CHECK(!c.disconnect());
}

TEST_CASE("Signal/Destroyed while ManagedConnection held")
{
    core::common::ManagedConnection mc;

    {
        core::common::Signal<int> signal;
        unsigned int count = 0;

        mc = signal.connect([&count](int a) {
            CHECK(a == 5);
            count++;
        });

        signal.emit(5);
        CHECK(count == 1);
    }

    CHECK(!mc);
    CHECK(!mc.disconnect());
}
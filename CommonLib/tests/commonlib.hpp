//SELF
#include "CommonLib/Window/WindowNone.hpp"

//LIBS
#include <doctest/doctest.h>

//STD

TEST_CASE("WindowNone/isOpen & close")
{
    meh::common::WindowNone window({});
    CHECK(window.isOpen());
    window.close();
    CHECK(!window.isOpen());
}

TEST_CASE("WindowNone/Send & Poll")
{
    meh::common::WindowNone window({});
    meh::common::Event event;
    CHECK(std::holds_alternative<meh::common::EventNone>(event));
    CHECK(!window.poll(event));
    CHECK(std::holds_alternative<meh::common::EventNone>(event));

    window.send(meh::common::EventQuit{});
    auto found_event = window.poll(event);
    CHECK(found_event);
    CHECK(std::holds_alternative<meh::common::EventQuit>(event));
    CHECK(!window.poll(event));
}

struct MyEvent : public meh::common::EventCustom
{
    MyEvent(std::string s)
        : meh::common::EventCustom(type_v)
        , super_secret(std::move(s))
    {
    }

    std::string super_secret;
    static constexpr std::int32_t type_v = 1;
};

TEST_CASE("WindowNone/Send & Poll Custom")
{
    meh::common::WindowNone window({});
    meh::common::Event event;
    CHECK(std::holds_alternative<meh::common::EventNone>(event));
    CHECK(!window.poll(event));
    CHECK(std::holds_alternative<meh::common::EventNone>(event));

    window.send(std::make_unique<MyEvent>("Hello World"));
    auto found_event = window.poll(event);
    CHECK(found_event);
    CHECK(std::holds_alternative<std::unique_ptr<meh::common::EventCustom>>(event));

    auto custom_event = std::get<std::unique_ptr<meh::common::EventCustom>>(std::move(event));
    auto* my_event = custom_event->as<MyEvent>();
    REQUIRE(my_event);
    CHECK(my_event->super_secret == "Hello World");

    CHECK(!window.poll(event));
}
#pragma once

//SELF
#include "Keys.hpp"

//LIBS

//STD
#include <variant>
#include <memory>

namespace meh::common
{

template <class... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

struct EventNone
{};

struct EventQuit
{};
struct EventClose
{};

struct EventKey
{
    Key key{};
    bool down = false;
    int scancode = 0;
};

struct EventMouseMove
{
    int x = 0;
    int y = 0;
    int xrel = 0;
    int yrel = 0;
};

struct EventMouseButton
{
    Button button{};
    bool down = false;
    int x = 0;
    int y = 0;
};

struct EventMouseWheel
{
    int horizontal = 0;
    int vertical = 0;
};

struct EventFocus
{
    bool focused = false;
};

struct EventVisibility
{
    enum class Visibility
    {
        Hidden,
        Shown,
        Exposed,
        Minimized,
        Maximized,
        Restored,
    };

    Visibility visibility{};
};

struct EventCharacter
{
    unsigned int character = 0;
};

struct EventMouseEnter
{
    bool entered = false;
};

struct EventDeviceChange
{
};

/* Inherit from this event */
struct EventCustom
{
    EventCustom(std::int32_t t)
        : type(t)
    {
    }
    virtual ~EventCustom() noexcept = default;

    [[nodiscard]] std::int32_t getType() const { return type; }

    template <typename T>
    [[nodiscard]] bool is() const
    {
        static_assert(std::is_base_of_v<EventCustom, T>, "This type is not derived from meh::common::EventCustom");
        return T::type_v == type;
    }

    template <typename T>
    [[nodiscard]] T* as()
    {
        static_assert(std::is_base_of_v<EventCustom, T>, "This type is not derived from meh::common::EventCustom");
        return T::type_v == type ? static_cast<T*>(this) : nullptr;
    }

    template <typename T>
    [[nodiscard]] const T* as() const
    {
        static_assert(std::is_base_of_v<EventCustom, T>, "This type is not derived from meh::common::EventCustom");
        return T::type_v == type ? static_cast<const T*>(this) : nullptr;
    }

private:
    std::int32_t type = 0;
};

using Event = std::variant<
    EventNone,
    EventQuit,
    EventClose,
    EventKey,
    EventMouseMove,
    EventMouseButton,
    EventMouseWheel,
    EventFocus,
    EventVisibility,
    EventCharacter,
    EventMouseEnter,
    EventDeviceChange,
    std::unique_ptr<EventCustom>>;
} // namespace meh::common
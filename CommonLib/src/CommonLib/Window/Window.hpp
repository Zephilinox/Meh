#pragma once

//SELF

//LIBS

//STD
#include <string>

namespace meh::common
{

class Window
{
public:
    struct Settings
    {
        unsigned int width{};
        unsigned int height{};
        std::string title{};
        bool vsync{ false };
    };

    Window(std::int32_t t, Settings s)
        : type(t)
        , settings(std::move(s))
    {
    }

    Window(const Window&) noexcept = delete;
    Window(Window&&) noexcept = delete;
    Window& operator=(Window&&) noexcept = delete;
    Window& operator=(const Window&) noexcept = delete;
    virtual ~Window() noexcept = default;

    //virtual bool poll(Event& e) = 0;
    [[nodiscard]] virtual bool isOpen() const = 0;
    [[nodiscard]] virtual bool isVerticalSyncEnabled() const = 0;

    [[nodiscard]] virtual unsigned int getWidth() const = 0;
    [[nodiscard]] virtual unsigned int getHeight() const = 0;

    virtual void close() = 0;
    virtual void clear(int r, int g, int b) = 0;
    virtual void display() = 0;

    virtual void setVerticalSyncEnabled(bool enabled) = 0;
    virtual void setWidth(unsigned int width) = 0;
    virtual void setHeight(unsigned int height) = 0;

    [[nodiscard]] std::int32_t getType() const { return type; }

    template <typename T>
    [[nodiscard]] bool is()
    {
        static_assert(std::is_base_of_v<Window, T>, "This type is not derived from meh::common::Window");
        return T::type_v == type;
    }

    template <typename T>
    [[nodiscard]] T* as()
    {
        static_assert(std::is_base_of_v<Window, T>, "This type is not derived from meh::common::Window");
        return T::type_v == type ? static_cast<T*>(this) : nullptr;
    }

    template <typename T>
    [[nodiscard]] const T* as() const
    {
        static_assert(std::is_base_of_v<Window, T>, "This type is not derived from meh::common::Window");
        return T::type_v == type ? static_cast<const T*>(this) : nullptr;
    }

protected:
    std::int32_t type;
    Settings settings;
};

} // namespace meh::common
#pragma once

//SELF
#include "CoreCommon/Window/Window.hpp"
#include "CoreCommon/Input/Events.hpp"

//LIBS

//STD

struct ImGuiIO;

namespace core::common
{

class IMGUI
{
public:
    IMGUI(std::int32_t t)
        : type(t)
    {
    }

    IMGUI(const IMGUI&) = delete;
    IMGUI(IMGUI&&) = delete;
    IMGUI& operator=(const IMGUI&) = delete;
    IMGUI& operator=(IMGUI&&) = delete;
    virtual ~IMGUI() noexcept = default;

    /* returns true if the event was processed. caller may use this to stop the event propagating */
    virtual bool process(const Event& event) = 0;
    virtual void update(const Window& window) = 0;
    virtual void render() = 0;

    [[nodiscard]] virtual ImGuiIO* getRawIMGUI() const = 0;

    [[nodiscard]] std::int32_t getType() const { return type; }

    template <typename T>
    [[nodiscard]] bool is() const
    {
        static_assert(std::is_base_of_v<IMGUI, T>, "This type is not derived from core::common::IMGUI");
        return T::type_v == type;
    }

    template <typename T>
    [[nodiscard]] T* as()
    {
        static_assert(std::is_base_of_v<IMGUI, T>, "This type is not derived from core::common::IMGUI");
        return T::type_v == type ? static_cast<T*>(this) : nullptr;
    }

    template <typename T>
    [[nodiscard]] const T* as() const
    {
        static_assert(std::is_base_of_v<IMGUI, T>, "This type is not derived from core::common::IMGUI");
        return T::type_v == type ? static_cast<const T*>(this) : nullptr;
    }

protected:
    std::int32_t type;
};

} // namespace core::common
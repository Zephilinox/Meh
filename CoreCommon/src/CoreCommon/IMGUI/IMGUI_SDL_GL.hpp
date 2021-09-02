#pragma once

//SELF
#include "CoreCommon/IMGUI/IMGUI.hpp"

//LIBS

//STD

namespace core::common
{

class IMGUI_SDL_GL final : public IMGUI
{
public:
    IMGUI_SDL_GL(const Window& window, void* sdl_gl_context);
    IMGUI_SDL_GL(const IMGUI&) = delete;
    IMGUI_SDL_GL(IMGUI&&) = delete;
    IMGUI_SDL_GL& operator=(const IMGUI&) = delete;
    IMGUI_SDL_GL& operator=(IMGUI&&) = delete;
    ~IMGUI_SDL_GL() noexcept final;

    /* returns true if the event was processed. caller may use this to stop the event propagating */
    bool process(const Event& event) final;
    void update(const Window& window) final;
    void render() final;

    [[nodiscard]] ImGuiIO* getRawIMGUI() const final;

    static constexpr std::int32_t type_v = 2;

private:
    ImGuiIO* io = nullptr;
};

} // namespace core::common
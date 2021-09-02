#include "IMGUI_SDL_GL.hpp"

//SELF
#include "CoreCommon/Window/WindowSDL.hpp"

//LIBS
#include <cstring> //memcpy for SDL
#include <SDL.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

//STD

using namespace core::common;

IMGUI_SDL_GL::IMGUI_SDL_GL(const Window& window, void* sdl_gl_context)
    : IMGUI(type_v)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();

    //todo: IMGUI needs to know about openGL?
    ImGui_ImplSDL2_InitForOpenGL(window.as<WindowSDL>()->getRawWindow(), sdl_gl_context);
    ImGui_ImplOpenGL3_Init("#version 100"); // WebGL1 with OpenGLES2
    //ImGui_ImplOpenGL3_Init("#version 300 es"); // WebGL2 with OpenGLES2
    ImGui::StyleColorsClassic();
}

IMGUI_SDL_GL::~IMGUI_SDL_GL() noexcept
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

//note: this is copy+pasted from the IMGUI SDL .cpp, so could be iffy casting to both
//the big hacks
struct ImGui_ImplSDL2_Data
{
    SDL_Window* Window;
    Uint64 Time;
    bool MousePressed[3];                             // NOLINT
    SDL_Cursor* MouseCursors[ImGuiMouseCursor_COUNT]; // NOLINT
    char* ClipboardTextData;
    bool MouseCanUseGlobalState;

    ImGui_ImplSDL2_Data() { memset(this, 0, sizeof(*this)); } // NOLINT
};

bool IMGUI_SDL_GL::process(const Event& event)
{
    auto* backend = ImGui::GetCurrentContext()
                        ? static_cast<ImGui_ImplSDL2_Data*>(ImGui::GetIO().BackendPlatformUserData)
                        : nullptr;

    auto visitor = overload{
        [&](const EventKey& e) {
            int key = e.scancode;
            IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io->KeysDown));
            io->KeysDown[key] = e.down;

            //todo: handle modifier keys ourselves
            io->KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
            io->KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
            io->KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
#ifdef _WIN32
            io->KeySuper = false;
#else
            io->KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
#endif
        },
        [&](const EventMouseButton& e) {
            if (e.button == Button::Left)
                backend->MousePressed[0] = true;
            else if (e.button == Button::Right)
                backend->MousePressed[1] = true;
            else if (e.button == Button::Middle)
                backend->MousePressed[2] = true;
        },
        [&](const EventMouseWheel& e) {
            if (e.horizontal > 0)
                io->MouseWheelH += 1;
            else if (e.horizontal < 0)
                io->MouseWheelH -= 1;

            if (e.vertical > 0)
                io->MouseWheel += 1;
            else if (e.vertical < 0)
                io->MouseWheel -= 1;
        },
        [&](const EventText& e) {
            io->AddInputCharactersUTF8(e.text.data());
        },
        [&](const EventFocus& e) {
            io->AddFocusEvent(e.focused);
        },
        [&](auto&&) {
        }
    };

    std::visit(visitor, event);
    return io->WantCaptureKeyboard || io->WantCaptureMouse;
}

void IMGUI_SDL_GL::update(const Window& window)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window.as<WindowSDL>()->getRawWindow());
    ImGui::NewFrame();
}

void IMGUI_SDL_GL::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImGuiIO* IMGUI_SDL_GL::getRawIMGUI() const
{
    return io;
}

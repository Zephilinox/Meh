#pragma once

//SELF
#include "CommonLib/Input/Keys.hpp"
#include "CommonLib/Input/Events.hpp"

//LIBS

//STD
#include <array>

namespace meh::common
{

/* note: note reliable at low update rates. does not track multiple inputs of the same kind within a single frame */
class Input
{
public:
    enum class State : int
    {
        Unheld,
        HeldDown,
        JustReleased,
        JustPressed,
    };

    Input();

    /* Process an event, updating the input state */
    void process(const Event& event);
    /* Prepare for new input events by updating the previous input states */
    void prepare();

    /* Returns true if the key is Up regardless of its previous state */
    [[nodiscard]] bool isKeyUp(Key key) const;
    /* Returns true if the key is Down regardless of its previous state */
    [[nodiscard]] bool isKeyDown(Key key) const;
    /* Returns true if the key is Down when it was previously Up */
    [[nodiscard]] bool isKeyReleased(Key key) const;
    /* Returns true if the key is Up when it was previously Down */
    [[nodiscard]] bool isKeyPressed(Key key) const;

    [[nodiscard]] State getPreviousKeyState(Key key) const;
    [[nodiscard]] State getCurrentKeyState(Key key) const;

    /* Returns true if the button is Up regardless of its previous state */
    [[nodiscard]] bool isMouseButtonUp(Button button) const;
    /* Returns true if the button is Down regardless of its previous state */
    [[nodiscard]] bool isMouseButtonDown(Button button) const;
    /* Returns true if the button is Down when it was previously Up */
    [[nodiscard]] bool isMouseButtonPressed(Button button) const;
    /* Returns true if the button is Up when it was previously Down */
    [[nodiscard]] bool isMouseButtonReleased(Button button) const;

    [[nodiscard]] State getPreviousButtonState(Button button) const;
    [[nodiscard]] State getCurrentButtonState(Button button) const;

    [[nodiscard]] bool hasMouseMoved() const;
    [[nodiscard]] std::pair<int, int> getCurrentMouseScreenPos() const;
    [[nodiscard]] std::pair<int, int> getPreviousMouseScreenPos() const;
    /* Returns the delta from the previous position to the current position. previous position + delta = current position */
    [[nodiscard]] std::pair<int, int> getMouseScreenPosDelta() const;

private:
    std::array<State, static_cast<std::size_t>(Key::KeyCount)> keys_last_frame;
    std::array<State, static_cast<std::size_t>(Key::KeyCount)> keys_this_frame;

    std::array<State, static_cast<std::size_t>(Button::ButtonCount)> mouse_buttons_last_frame;
    std::array<State, static_cast<std::size_t>(Button::ButtonCount)> mouse_buttons_this_frame;

    //todo: don't use pair
    std::pair<int, int> mouse_screen_pos_previous;
    std::pair<int, int> mouse_screen_pos_current;
};

} // namespace meh::common
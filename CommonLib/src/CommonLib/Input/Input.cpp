#include "Input.hpp"

//SELF

//LIBS

//STD
#include <cassert>

using namespace meh::common;

Input::Input()
    : keys_last_frame{}
    , keys_this_frame{}
    , mouse_buttons_last_frame{}
    , mouse_buttons_this_frame{}
    , mouse_screen_pos_previous{ 0, 0 }
    , mouse_screen_pos_current{ 0, 0 }
{
    keys_last_frame.fill(State::Unheld);
    keys_this_frame.fill(State::Unheld);

    mouse_buttons_last_frame.fill(State::Unheld);
    mouse_buttons_this_frame.fill(State::Unheld);
}

void Input::process(const Event& event)
{
    const auto visitor = overload{
        [this](const EventKey& e) {
            if (e.key == Key::Unknown)
                return; //todo: I'd rather not need to do this error checking

            const auto key = static_cast<std::size_t>(e.key);

            State state;

            if (this->keys_last_frame[key] == State::JustPressed
                || this->keys_last_frame[key] == State::HeldDown)
            {
                if (e.down)
                    state = State::HeldDown;
                else
                    state = State::JustReleased;
            }
            else if (this->keys_last_frame[key] == State::JustReleased
                     || this->keys_last_frame[key] == State::Unheld)
            {
                if (e.down)
                    state = State::JustPressed;
                else
                    state = State::Unheld;
            }
            else
            {
                throw; //unreachable
            }

            /*if (this->keys_this_frame[key] != state)
			{
				spdlog::info("State of key {} was {}, but is now {}",
					keyToString(e.key),
					magic_enum::enum_name(this->keys_this_frame[key]).data(),
					magic_enum::enum_name(state).data());
			}*/
            this->keys_this_frame[key] = state;
        },
        [this](const EventMouseButton& e) {
            if (e.button == Button::Unknown)
                return; //todo: I'd rather not need to do this error checking

            const auto button = static_cast<std::size_t>(e.button);

            State state;

            if (this->mouse_buttons_last_frame[button] == State::JustPressed
                || this->mouse_buttons_last_frame[button] == State::HeldDown)
            {
                if (e.down)
                    state = State::HeldDown;
                else
                    state = State::JustReleased;
            }
            else if (this->mouse_buttons_last_frame[button] == State::JustReleased
                     || this->mouse_buttons_last_frame[button] == State::Unheld)
            {
                if (e.down)
                    state = State::JustPressed;
                else
                    state = State::Unheld;
            }
            else
            {
                throw; //unreachable, todo: change code so this isn't needed
            }

            /*if (this->mouse_buttons_this_frame[button] != state)
			{
				spdlog::info("State of button {} was {}, but is now {}",
					buttonToString(e.button),
					magic_enum::enum_name(this->mouse_buttons_this_frame[button]).data(),
					magic_enum::enum_name(state).data());
			}*/
            this->mouse_buttons_this_frame[button] = state;
        },
        [this](const EventMouseMove& e) {
            this->mouse_screen_pos_current = { e.x, e.y };
        },
        [](auto&&) {

        }
    };

    std::visit(visitor, event);
}

void Input::prepare()
{
    for (size_t i = 0; i < keys_last_frame.size(); ++i)
    {
        keys_last_frame[i] = keys_this_frame[i];

        // If the key was JustPressed or JustReleased then transition the current state to the full hold/release state
        switch (keys_this_frame[i])
        {
        case State::Unheld:
        case State::HeldDown:
            break;
        case State::JustPressed:
            keys_this_frame[i] = State::HeldDown;
            break;
        case State::JustReleased:
            keys_this_frame[i] = State::Unheld;
            break;
        default:
            throw; // unreachable
        }
    }

    for (size_t i = 0; i < mouse_buttons_last_frame.size(); ++i)
    {
        mouse_buttons_last_frame[i] = mouse_buttons_this_frame[i];

        // If the button was JustPressed or JustReleased then transition the current state to the full hold/release state
        switch (mouse_buttons_this_frame[i])
        {
        case State::Unheld:
        case State::HeldDown:
            break;
        case State::JustPressed:
            mouse_buttons_this_frame[i] = State::HeldDown;
            break;
        case State::JustReleased:
            mouse_buttons_this_frame[i] = State::Unheld;
            break;
        default:
            throw; // unreachable
        }
    }

    mouse_screen_pos_previous = mouse_screen_pos_current;
}

bool Input::isKeyUp(Key key) const
{
    assert(key != Key::Unknown);
    const auto k = static_cast<std::size_t>(key);
    return (keys_this_frame[k] == State::Unheld || keys_this_frame[k] == State::JustReleased);
}

bool Input::isKeyReleased(Key key) const
{
    assert(key != Key::Unknown);
    const auto k = static_cast<std::size_t>(key);
    return (keys_this_frame[k] == State::JustReleased);
}

bool Input::isKeyPressed(Key key) const
{
    assert(key != Key::Unknown);
    const auto k = static_cast<std::size_t>(key);
    return (keys_this_frame[k] == State::JustPressed);
}

bool Input::isKeyDown(Key key) const
{
    assert(key != Key::Unknown);
    const auto k = static_cast<std::size_t>(key);
    return (keys_this_frame[k] == State::HeldDown || keys_this_frame[k] == State::JustPressed);
}

Input::State Input::getPreviousKeyState(Key key) const
{
    assert(key != Key::Unknown);
    return keys_last_frame[static_cast<std::size_t>(key)];
}

Input::State Input::getCurrentKeyState(Key key) const
{
    assert(key != Key::Unknown);
    return keys_this_frame[static_cast<std::size_t>(key)];
}

bool Input::isMouseButtonUp(Button button) const
{
    assert(button != Button::Unknown);
    const auto b = static_cast<std::size_t>(button);
    return (mouse_buttons_this_frame[b] == State::Unheld || mouse_buttons_this_frame[b] == State::JustReleased);
}

bool Input::isMouseButtonPressed(Button button) const
{
    assert(button != Button::Unknown);
    const auto b = static_cast<std::size_t>(button);
    return (mouse_buttons_this_frame[b] == State::JustPressed);
}

bool Input::isMouseButtonReleased(Button button) const
{
    assert(button != Button::Unknown);
    const auto b = static_cast<std::size_t>(button);
    return (mouse_buttons_this_frame[b] == State::JustReleased);
}

bool Input::isMouseButtonDown(Button button) const
{
    assert(button != Button::Unknown);
    const auto b = static_cast<std::size_t>(button);
    return (mouse_buttons_this_frame[b] == State::HeldDown || mouse_buttons_this_frame[b] == State::JustPressed);
}

Input::State Input::getPreviousButtonState(Button button) const
{
    assert(button != Button::Unknown);
    return mouse_buttons_last_frame[static_cast<std::size_t>(button)];
}

Input::State Input::getCurrentButtonState(Button button) const
{
    assert(button != Button::Unknown);
    return mouse_buttons_this_frame[static_cast<std::size_t>(button)];
}

bool meh::common::Input::hasMouseMoved() const
{
    //todo: if the screen moves...?
    const auto delta = getMouseScreenPosDelta();
    return delta.first == 0 && delta.second == 0;
}

std::pair<int, int> Input::getCurrentMouseScreenPos() const
{
    return mouse_screen_pos_current;
}

std::pair<int, int> Input::getPreviousMouseScreenPos() const
{
    return mouse_screen_pos_previous;
}

std::pair<int, int> Input::getMouseScreenPosDelta() const
{
    return {
        mouse_screen_pos_previous.second - mouse_screen_pos_current.second,
        mouse_screen_pos_previous.first - mouse_screen_pos_current.first
    };
}
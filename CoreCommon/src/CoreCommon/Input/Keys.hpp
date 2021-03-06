#pragma once

//SELF

//LIBS

//STD
#include <string>

namespace core::common
{

enum class Key : int
{
    Unknown = -1,

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,

    Escape,
    Tab,
    Capslock,
    Shift,
    Control,
    Alt,
    Command,
    Function,
    Menu,
    Enter,
    Backspace,
    Comma,
    Period,
    Slash,
    Backslash,
    Semicolon,
    Quote,
    Hash,
    LeftBracket,
    RightBracket,
    Dash,
    Space,

    PageUp,
    PageDown,
    Home,
    End,
    Delete,
    Insert,

    Minus,
    Plus,
    Divide,
    Multiply,

    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,

    Up,
    Down,
    Left,
    Right,

    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,

    Pause,
    PrintScreen,

    KeyCount,

    Windows = Command,
    Super = Command,
    Return = Enter,
    Fullstop = Period,
    Hyphen = Dash,
    Add = Plus,
    Forwardslash = Slash,
};

Key keyFromString(const std::string& str);
const char* keyToString(Key key);

enum class Button : int
{
    Unknown = -1,
    Left,
    Right,
    Middle,
    Button4,
    Button5,

    ButtonCount,
};

Button buttonFromString(const std::string& str);
const char* buttonToString(Button button);

} // namespace core::common
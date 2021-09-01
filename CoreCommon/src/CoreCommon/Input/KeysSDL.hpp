#pragma once

//SELF
#include "CoreCommon/Input/Keys.hpp"

//LIBS
#include <cstring> //memcpy for SDL
#include <SDL.h>
#include <spdlog/spdlog.h>

namespace core::common
{

Key SDLKeyConversion(SDL_Keycode sdl_key)
{
    if (sdl_key == SDLK_UNKNOWN)
        return Key::Unknown;

    if (sdl_key == SDLK_RETURN)
        return Key::Return;

    if (sdl_key == SDLK_ESCAPE)
        return Key::Escape;

    if (sdl_key == SDLK_BACKSPACE)
        return Key::Backspace;

    if (sdl_key == SDLK_TAB)
        return Key::Tab;

    if (sdl_key == SDLK_SPACE)
        return Key::Space;

    if (sdl_key == SDLK_EXCLAIM)
        return Key::Unknown;

    if (sdl_key == SDLK_QUOTEDBL)
        return Key::Quote;

    if (sdl_key == SDLK_HASH)
        return Key::Hash;

    if (sdl_key == SDLK_PERCENT)
        return Key::Unknown;

    if (sdl_key == SDLK_DOLLAR)
        return Key::Unknown;

    if (sdl_key == SDLK_AMPERSAND)
        return Key::Unknown;

    if (sdl_key == SDLK_QUOTE)
        return Key::Unknown;

    if (sdl_key == SDLK_LEFTPAREN)
        return Key::LeftBracket;

    if (sdl_key == SDLK_RIGHTPAREN)
        return Key::RightBracket;

    if (sdl_key == SDLK_ASTERISK)
        return Key::Multiply;

    if (sdl_key == SDLK_PLUS)
        return Key::Plus;

    if (sdl_key == SDLK_COMMA)
        return Key::Comma;

    if (sdl_key == SDLK_MINUS)
        return Key::Minus;

    if (sdl_key == SDLK_PERIOD)
        return Key::Period;

    if (sdl_key == SDLK_SLASH)
        return Key::Slash;

    if (sdl_key == SDLK_0)
        return Key::Num0;

    if (sdl_key == SDLK_1)
        return Key::Num1;

    if (sdl_key == SDLK_2)
        return Key::Num2;

    if (sdl_key == SDLK_3)
        return Key::Num3;

    if (sdl_key == SDLK_4)
        return Key::Num4;

    if (sdl_key == SDLK_5)
        return Key::Num5;

    if (sdl_key == SDLK_6)
        return Key::Num6;

    if (sdl_key == SDLK_7)
        return Key::Num7;

    if (sdl_key == SDLK_8)
        return Key::Num8;

    if (sdl_key == SDLK_9)
        return Key::Num9;

    if (sdl_key == SDLK_COLON)
        return Key::Unknown;

    if (sdl_key == SDLK_SEMICOLON)
        return Key::Semicolon;

    if (sdl_key == SDLK_LESS)
        return Key::Unknown;

    if (sdl_key == SDLK_EQUALS)
        return Key::Unknown;

    if (sdl_key == SDLK_GREATER)
        return Key::Unknown;

    if (sdl_key == SDLK_QUESTION)
        return Key::Unknown;

    if (sdl_key == SDLK_AT)
        return Key::Unknown;

    if (sdl_key == SDLK_LEFTBRACKET)
        return Key::Unknown;

    if (sdl_key == SDLK_BACKSLASH)
        return Key::Backslash;

    if (sdl_key == SDLK_RIGHTBRACKET)
        return Key::Unknown;

    if (sdl_key == SDLK_CARET)
        return Key::Unknown;

    if (sdl_key == SDLK_UNDERSCORE)
        return Key::Unknown;

    if (sdl_key == SDLK_BACKQUOTE)
        return Key::Unknown;

    if (sdl_key == SDLK_a)
        return Key::A;

    if (sdl_key == SDLK_b)
        return Key::B;

    if (sdl_key == SDLK_c)
        return Key::C;

    if (sdl_key == SDLK_d)
        return Key::D;

    if (sdl_key == SDLK_e)
        return Key::E;

    if (sdl_key == SDLK_f)
        return Key::F;

    if (sdl_key == SDLK_g)
        return Key::G;

    if (sdl_key == SDLK_h)
        return Key::H;

    if (sdl_key == SDLK_i)
        return Key::I;

    if (sdl_key == SDLK_j)
        return Key::J;

    if (sdl_key == SDLK_k)
        return Key::K;

    if (sdl_key == SDLK_l)
        return Key::L;

    if (sdl_key == SDLK_m)
        return Key::M;

    if (sdl_key == SDLK_n)
        return Key::N;

    if (sdl_key == SDLK_o)
        return Key::O;

    if (sdl_key == SDLK_p)
        return Key::P;

    if (sdl_key == SDLK_q)
        return Key::Q;

    if (sdl_key == SDLK_r)
        return Key::R;

    if (sdl_key == SDLK_s)
        return Key::S;

    if (sdl_key == SDLK_t)
        return Key::T;

    if (sdl_key == SDLK_u)
        return Key::U;

    if (sdl_key == SDLK_v)
        return Key::V;

    if (sdl_key == SDLK_w)
        return Key::W;

    if (sdl_key == SDLK_x)
        return Key::X;

    if (sdl_key == SDLK_y)
        return Key::Y;

    if (sdl_key == SDLK_z)
        return Key::Z;

    if (sdl_key == SDLK_CAPSLOCK)
        return Key::Capslock;

    if (sdl_key == SDLK_F1)
        return Key::F1;

    if (sdl_key == SDLK_F2)
        return Key::F2;

    if (sdl_key == SDLK_F3)
        return Key::F3;

    if (sdl_key == SDLK_F4)
        return Key::F4;

    if (sdl_key == SDLK_F5)
        return Key::F5;

    if (sdl_key == SDLK_F6)
        return Key::F6;

    if (sdl_key == SDLK_F7)
        return Key::F7;

    if (sdl_key == SDLK_F8)
        return Key::F8;

    if (sdl_key == SDLK_F9)
        return Key::F9;

    if (sdl_key == SDLK_F10)
        return Key::F10;

    if (sdl_key == SDLK_F11)
        return Key::F11;

    if (sdl_key == SDLK_F12)
        return Key::F12;

    if (sdl_key == SDLK_F13)
        return Key::Unknown;

    if (sdl_key == SDLK_F14)
        return Key::Unknown;

    if (sdl_key == SDLK_F15)
        return Key::Unknown;

    if (sdl_key == SDLK_F16)
        return Key::Unknown;

    if (sdl_key == SDLK_F17)
        return Key::Unknown;

    if (sdl_key == SDLK_F18)
        return Key::Unknown;

    if (sdl_key == SDLK_F19)
        return Key::Unknown;

    if (sdl_key == SDLK_F20)
        return Key::Unknown;

    if (sdl_key == SDLK_F21)
        return Key::Unknown;

    if (sdl_key == SDLK_F22)
        return Key::Unknown;

    if (sdl_key == SDLK_F23)
        return Key::Unknown;

    if (sdl_key == SDLK_F24)
        return Key::Unknown;

    if (sdl_key == SDLK_PRINTSCREEN)
        return Key::PrintScreen;
    if (sdl_key == SDLK_SCROLLLOCK)
        return Key::Unknown;
    if (sdl_key == SDLK_PAUSE)
        return Key::Pause;
    if (sdl_key == SDLK_INSERT)
        return Key::Insert;
    if (sdl_key == SDLK_HOME)
        return Key::Home;
    if (sdl_key == SDLK_PAGEUP)
        return Key::PageUp;
    if (sdl_key == SDLK_DELETE)
        return Key::Delete;
    if (sdl_key == SDLK_END)
        return Key::End;
    if (sdl_key == SDLK_PAGEDOWN)
        return Key::PageDown;
    if (sdl_key == SDLK_RIGHT)
        return Key::Right;
    if (sdl_key == SDLK_LEFT)
        return Key::Left;
    if (sdl_key == SDLK_DOWN)
        return Key::Down;
    if (sdl_key == SDLK_UP)
        return Key::Up;
    if (sdl_key == SDLK_NUMLOCKCLEAR)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_DIVIDE)
        return Key::Divide;
    if (sdl_key == SDLK_KP_MULTIPLY)
        return Key::Multiply;
    if (sdl_key == SDLK_KP_MINUS)
        return Key::Minus;
    if (sdl_key == SDLK_KP_PLUS)
        return Key::Plus;
    if (sdl_key == SDLK_KP_ENTER)
        return Key::Enter;
    if (sdl_key == SDLK_KP_0)
        return Key::Numpad0;
    if (sdl_key == SDLK_KP_1)
        return Key::Numpad1;
    if (sdl_key == SDLK_KP_2)
        return Key::Numpad2;
    if (sdl_key == SDLK_KP_3)
        return Key::Numpad3;
    if (sdl_key == SDLK_KP_4)
        return Key::Numpad4;
    if (sdl_key == SDLK_KP_5)
        return Key::Numpad5;
    if (sdl_key == SDLK_KP_6)
        return Key::Numpad6;
    if (sdl_key == SDLK_KP_7)
        return Key::Numpad7;
    if (sdl_key == SDLK_KP_8)
        return Key::Numpad8;
    if (sdl_key == SDLK_KP_9)
        return Key::Numpad9;
    if (sdl_key == SDLK_KP_PERIOD)
        return Key::Period;
    if (sdl_key == SDLK_APPLICATION)
        return Key::Unknown;
    if (sdl_key == SDLK_POWER)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_EQUALS)
        return Key::Unknown;
    if (sdl_key == SDLK_EXECUTE)
        return Key::Unknown;
    if (sdl_key == SDLK_HELP)
        return Key::Unknown;
    if (sdl_key == SDLK_MENU)
        return Key::Unknown;
    if (sdl_key == SDLK_SELECT)
        return Key::Unknown;
    if (sdl_key == SDLK_STOP)
        return Key::Unknown;
    if (sdl_key == SDLK_AGAIN)
        return Key::Unknown;
    if (sdl_key == SDLK_UNDO)
        return Key::Unknown;
    if (sdl_key == SDLK_CUT)
        return Key::Unknown;
    if (sdl_key == SDLK_COPY)
        return Key::Unknown;
    if (sdl_key == SDLK_PASTE)
        return Key::Unknown;
    if (sdl_key == SDLK_FIND)
        return Key::Unknown;
    if (sdl_key == SDLK_MUTE)
        return Key::Unknown;
    if (sdl_key == SDLK_VOLUMEUP)
        return Key::Unknown;
    if (sdl_key == SDLK_VOLUMEDOWN)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_COMMA)
        return Key::Comma;
    if (sdl_key == SDLK_KP_EQUALSAS400)
        return Key::Unknown;
    if (sdl_key == SDLK_ALTERASE)
        return Key::Unknown;
    if (sdl_key == SDLK_SYSREQ)
        return Key::Unknown;
    if (sdl_key == SDLK_CANCEL)
        return Key::Unknown;
    if (sdl_key == SDLK_CLEAR)
        return Key::Unknown;
    if (sdl_key == SDLK_PRIOR)
        return Key::Unknown;
    if (sdl_key == SDLK_RETURN2)
        return Key::Unknown;
    if (sdl_key == SDLK_SEPARATOR)
        return Key::Unknown;
    if (sdl_key == SDLK_OUT)
        return Key::Unknown;
    if (sdl_key == SDLK_OPER)
        return Key::Unknown;
    if (sdl_key == SDLK_CLEARAGAIN)
        return Key::Unknown;
    if (sdl_key == SDLK_CRSEL)
        return Key::Unknown;
    if (sdl_key == SDLK_EXSEL)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_00)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_000)
        return Key::Unknown;
    if (sdl_key == SDLK_THOUSANDSSEPARATOR)
        return Key::Unknown;
    if (sdl_key == SDLK_DECIMALSEPARATOR)
        return Key::Unknown;
    if (sdl_key == SDLK_CURRENCYUNIT)
        return Key::Unknown;
    if (sdl_key == SDLK_CURRENCYSUBUNIT)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_LEFTPAREN)
        return Key::LeftBracket;
    if (sdl_key == SDLK_KP_RIGHTPAREN)
        return Key::RightBracket;
    if (sdl_key == SDLK_KP_LEFTBRACE)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_RIGHTBRACE)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_TAB)
        return Key::Tab;
    if (sdl_key == SDLK_KP_BACKSPACE)
        return Key::Backspace;
    if (sdl_key == SDLK_KP_A)
        return Key::A;
    if (sdl_key == SDLK_KP_B)
        return Key::B;
    if (sdl_key == SDLK_KP_C)
        return Key::C;
    if (sdl_key == SDLK_KP_D)
        return Key::D;
    if (sdl_key == SDLK_KP_E)
        return Key::E;
    if (sdl_key == SDLK_KP_F)
        return Key::F;
    if (sdl_key == SDLK_KP_XOR)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_POWER)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_PERCENT)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_LESS)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_GREATER)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_AMPERSAND)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_DBLAMPERSAND)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_VERTICALBAR)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_DBLVERTICALBAR)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_COLON)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_HASH)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_SPACE)
        return Key::Space;
    if (sdl_key == SDLK_KP_AT)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_EXCLAM)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_MEMSTORE)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_MEMRECALL)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_MEMCLEAR)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_MEMADD)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_MEMSUBTRACT)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_MEMMULTIPLY)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_MEMDIVIDE)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_PLUSMINUS)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_CLEAR)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_CLEARENTRY)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_BINARY)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_OCTAL)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_DECIMAL)
        return Key::Unknown;
    if (sdl_key == SDLK_KP_HEXADECIMAL)
        return Key::Unknown;
    if (sdl_key == SDLK_LCTRL)
        return Key::Control;
    if (sdl_key == SDLK_LSHIFT)
        return Key::Shift;
    if (sdl_key == SDLK_LALT)
        return Key::Alt;
    if (sdl_key == SDLK_LGUI)
        return Key::Unknown;
    if (sdl_key == SDLK_RCTRL)
        return Key::Control;
    if (sdl_key == SDLK_RSHIFT)
        return Key::Shift;
    if (sdl_key == SDLK_RALT)
        return Key::Alt;
    if (sdl_key == SDLK_RGUI)
        return Key::Unknown;
    if (sdl_key == SDLK_MODE)
        return Key::Unknown;
    if (sdl_key == SDLK_AUDIONEXT)
        return Key::Unknown;
    if (sdl_key == SDLK_AUDIOPREV)
        return Key::Unknown;
    if (sdl_key == SDLK_AUDIOSTOP)
        return Key::Unknown;
    if (sdl_key == SDLK_AUDIOPLAY)
        return Key::Unknown;
    if (sdl_key == SDLK_AUDIOMUTE)
        return Key::Unknown;
    if (sdl_key == SDLK_MEDIASELECT)
        return Key::Unknown;
    if (sdl_key == SDLK_WWW)
        return Key::Unknown;
    if (sdl_key == SDLK_MAIL)
        return Key::Unknown;
    if (sdl_key == SDLK_CALCULATOR)
        return Key::Unknown;
    if (sdl_key == SDLK_COMPUTER)
        return Key::Unknown;
    if (sdl_key == SDLK_AC_SEARCH)
        return Key::Unknown;
    if (sdl_key == SDLK_AC_HOME)
        return Key::Unknown;
    if (sdl_key == SDLK_AC_BACK)
        return Key::Unknown;
    if (sdl_key == SDLK_AC_FORWARD)
        return Key::Unknown;
    if (sdl_key == SDLK_AC_STOP)
        return Key::Unknown;
    if (sdl_key == SDLK_AC_REFRESH)
        return Key::Unknown;
    if (sdl_key == SDLK_AC_BOOKMARKS)
        return Key::Unknown;
    if (sdl_key == SDLK_BRIGHTNESSDOWN)
        return Key::Unknown;
    if (sdl_key == SDLK_BRIGHTNESSUP)
        return Key::Unknown;
    if (sdl_key == SDLK_DISPLAYSWITCH)
        return Key::Unknown;
    if (sdl_key == SDLK_KBDILLUMTOGGLE)
        return Key::Unknown;
    if (sdl_key == SDLK_KBDILLUMDOWN)
        return Key::Unknown;
    if (sdl_key == SDLK_KBDILLUMUP)
        return Key::Unknown;
    if (sdl_key == SDLK_EJECT)
        return Key::Unknown;
    if (sdl_key == SDLK_SLEEP)
        return Key::Unknown;
    if (sdl_key == SDLK_APP1)
        return Key::Unknown;
    if (sdl_key == SDLK_APP2)
        return Key::Unknown;
    if (sdl_key == SDLK_APP2)
        return Key::Unknown;
    if (sdl_key == SDLK_AUDIOFASTFORWARD)
        return Key::Unknown;

    spdlog::error("Unknown SDL key {} when converting to actual key", sdl_key);
    return Key::Unknown;
}

Button SDLButtonConversion(int sdl_button)
{
    if (sdl_button == SDL_BUTTON_LEFT)
        return Button::Left;

    if (sdl_button == SDL_BUTTON_MIDDLE)
        return Button::Middle;

    if (sdl_button == SDL_BUTTON_RIGHT)
        return Button::Right;

    if (sdl_button == SDL_BUTTON_X1)
        return Button::Button4;

    if (sdl_button == SDL_BUTTON_X2)
        return Button::Button5;

    spdlog::error("Unknown SDL button {} when converting to actual button", sdl_button);
    return Button::Unknown;
}

} // namespace core::common
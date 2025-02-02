/************************************************************************************
*                                                                                   *
*   deepnova 0.1.0.0 - https://github.com/fkoppe/deepnova                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2024 Felix Koppe <fkoppe@web.de>                                  *
*                                                                                   *
*   This program is free software: you can redistribute it and/or modify            *
*   it under the terms of the GNU Affero General Public License as published        *
*   by the Free Software Foundation, either version 3 of the License, or            *
*   (at your option) any later version.                                             *
*                                                                                   *
*   This program is distributed in the hope that it will be useful,                 *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   *
*   GNU Affero General Public License for more details.                             *
*                                                                                   *
*   You should have received a copy of the GNU Affero General Public License        *
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.          *
*                                                                                   *
************************************************************************************/

#if !defined(___DEEP___EVENT_DATA_H)
#define ___DEEP___EVENT_DATA_H

#include <dark/core/std.h>
#include <dark/random/uuid4.h>

typedef enum Deep_Mouse_Button Deep_Mouse_Button;
enum Deep_Mouse_Button
{
    ___DEEP_MOUSE_BUTTON_MIN,
    DEEP_MOUSE_BUTTON_UNKNOWN,
    DEEP_MOUSE_BUTTON_LEFT,
    DEEP_MOUSE_BUTTON_RIGHT,
    DEEP_MOUSE_BUTTON_MIDDLE,
    DEEP_MOUSE_BUTTON_EXTRA_1,
    DEEP_MOUSE_BUTTON_EXTRA_2,
    DEEP_MOUSE_BUTTON_EXTRA_3,
    DEEP_MOUSE_BUTTON_EXTRA_4,
    DEEP_MOUSE_BUTTON_EXTRA_5,
    ___DEEP_MOUSE_BUTTON_MAX,
};

typedef enum Deep_Key_Modifier Deep_Key_Modifier;
enum Deep_Key_Modifier
{
    ___DEEP_KEY_MODIFIER_MIN,
    DEEP_KEY_MODIFIER_NONE      = 0,
    DEEP_KEY_MODIFIER_SHIFT     = 1 << 0,
    DEEP_KEY_MODIFIER_CONTROLL  = 1 << 1,
    DEEP_KEY_MODIFIER_ALT       = 1 << 2,
    DEEP_KEY_MODIFIER_SUPER     = 1 << 3,
    DEEP_KEY_MODIFIER_CAPS_LOCK = 1 << 4,
    DEEP_KEY_MODIFIER_NUM_LOCK  = 1 << 5,
    ___DEEP_KEY_MODIFIER_MAX    = 1 << 6,
};

typedef enum Deep_Key Deep_Key;
enum Deep_Key
{
    ___DEEP_KEY_MIN,
    DEEP_KEY_SPACE,
    DEEP_KEY_APOSTROPHE,
    DEEP_KEY_COMMA,
    DEEP_KEY_MINUS,
    DEEP_KEY_PERIOD,
    DEEP_KEY_SLASH,
    DEEP_KEY_0,
    DEEP_KEY_1,
    DEEP_KEY_2,
    DEEP_KEY_3,
    DEEP_KEY_4,
    DEEP_KEY_5,
    DEEP_KEY_6,
    DEEP_KEY_7,
    DEEP_KEY_8,
    DEEP_KEY_9,
    DEEP_KEY_SEMICOLON,
    DEEP_KEY_EQUAL,
    DEEP_KEY_A,
    DEEP_KEY_B,
    DEEP_KEY_C,
    DEEP_KEY_D,
    DEEP_KEY_E,
    DEEP_KEY_F,
    DEEP_KEY_G,
    DEEP_KEY_H,
    DEEP_KEY_I,
    DEEP_KEY_J,
    DEEP_KEY_K,
    DEEP_KEY_L,
    DEEP_KEY_M,
    DEEP_KEY_N,
    DEEP_KEY_O,
    DEEP_KEY_P,
    DEEP_KEY_Q,
    DEEP_KEY_R,
    DEEP_KEY_S,
    DEEP_KEY_T,
    DEEP_KEY_U,
    DEEP_KEY_V,
    DEEP_KEY_W,
    DEEP_KEY_X,
    DEEP_KEY_Y,
    DEEP_KEY_Z,
    DEEP_KEY_LEFT_BRACKET,
    DEEP_KEY_BACKSLASH,
    DEEP_KEY_RIGHT_BRACKET,
    DEEP_KEY_GRAVE_ACCENT,
    DEEP_KEY_WORLD_1,
    DEEP_KEY_WORLD_2,
    DEEP_KEY_ESCAPE,
    DEEP_KEY_ENTER,
    DEEP_KEY_TAB,
    DEEP_KEY_BACKSPACE,
    DEEP_KEY_INSERT,
    DEEP_KEY_DELETE,
    DEEP_KEY_RIGHT,
    DEEP_KEY_LEFT,
    DEEP_KEY_DOWN,
    DEEP_KEY_UP,
    DEEP_KEY_PAGE_UP,
    DEEP_KEY_PAGE_DOWN,
    DEEP_KEY_HOME,
    DEEP_KEY_END,
    DEEP_KEY_CAPS_LOCK,
    DEEP_KEY_SCROLL_LOCK,
    DEEP_KEY_NUM_LOCK,
    DEEP_KEY_PRINT_SCREEN,
    DEEP_KEY_PAUSE,
    DEEP_KEY_F1,
    DEEP_KEY_F2,
    DEEP_KEY_F3,
    DEEP_KEY_F4,
    DEEP_KEY_F5,
    DEEP_KEY_F6,
    DEEP_KEY_F7,
    DEEP_KEY_F8,
    DEEP_KEY_F9,
    DEEP_KEY_F10,
    DEEP_KEY_F11,
    DEEP_KEY_F12,
    DEEP_KEY_F13,
    DEEP_KEY_F14,
    DEEP_KEY_F15,
    DEEP_KEY_F16,
    DEEP_KEY_F17,
    DEEP_KEY_F18,
    DEEP_KEY_F19,
    DEEP_KEY_F20,
    DEEP_KEY_F21,
    DEEP_KEY_F22,
    DEEP_KEY_F23,
    DEEP_KEY_F24,
    DEEP_KEY_F25,
    DEEP_KEY_KP_0,
    DEEP_KEY_KP_1,
    DEEP_KEY_KP_2,
    DEEP_KEY_KP_3,
    DEEP_KEY_KP_4,
    DEEP_KEY_KP_5,
    DEEP_KEY_KP_6,
    DEEP_KEY_KP_7,
    DEEP_KEY_KP_8,
    DEEP_KEY_KP_9,
    DEEP_KEY_KP_DECIMAL,
    DEEP_KEY_KP_DIVIDE,
    DEEP_KEY_KP_MULTIPLY,
    DEEP_KEY_KP_SUBTRACT,
    DEEP_KEY_KP_ADD,
    DEEP_KEY_KP_ENTER,
    DEEP_KEY_KP_EQUAL,
    DEEP_KEY_LEFT_SHIFT,
    DEEP_KEY_LEFT_CONTROL,
    DEEP_KEY_LEFT_ALT,
    DEEP_KEY_LEFT_SUPER,
    DEEP_KEY_RIGHT_SHIFT,
    DEEP_KEY_RIGHT_CONTROL,
    DEEP_KEY_RIGHT_ALT,
    DEEP_KEY_RIGHT_SUPER,
    DEEP_KEY_MENU,
    DEEP_KEY_UNKNOWN,
    ___DEEP_KEY_MAX,
};

typedef enum Deep_Event_Type Deep_Event_Type;
enum Deep_Event_Type
{
    ___DEEP_EVENT_TYPE_MIN,
    DEEP_EVENT_TYPE_NONE,
    DEEP_EVENT_TYPE_WINDOW_MOVED,
    DEEP_EVENT_TYPE_WINDOW_RESIZED,
    DEEP_EVENT_TYPE_WINDOW_CLOSED,
    DEEP_EVENT_TYPE_WINDOW_REFRESHED,
    DEEP_EVENT_TYPE_WINDOW_FOCUSED,
    DEEP_EVENT_TYPE_WINDOW_UNFOCUSED,
    DEEP_EVENT_TYPE_WINDOW_ICONIFIED,
    DEEP_EVENT_TYPE_WINDOW_UNICONIFIED,
    DEEP_EVENT_TYPE_WINDOW_MAXIMIZED,
    DEEP_EVENT_TYPE_WINDOW_UNMAXIMIZED,
    DEEP_EVENT_TYPE_WINDOW_SCALE_CHANGED,
    DEEP_EVENT_TYPE_WINDOW_FRAMEBUFFER_RESIZED,
    DEEP_EVENT_TYPE_BUTTON_PRESSED,
    DEEP_EVENT_TYPE_BUTTON_RELEASED,
    DEEP_EVENT_TYPE_CURSOR_MOVED,
    DEEP_EVENT_TYPE_CURSOR_ENTERED,
    DEEP_EVENT_TYPE_CURSOR_LEFT,
    DEEP_EVENT_TYPE_SCROLLED,
    DEEP_EVENT_TYPE_KEY_PRESSED,
    DEEP_EVENT_TYPE_KEY_REPEATED,
    DEEP_EVENT_TYPE_KEY_RELEASED,
    DEEP_EVENT_TYPE_CODEPOINT_INPUT,
    DEEP_EVENT_TYPE_FILE_DROPPED,
    DEEP_EVENT_TYPE_MONITOR_CONNECTED,
    DEEP_EVENT_TYPE_MONITOR_DISCONNECTED,
    DEEP_EVENT_TYPE_JOYSTICK_CONNECTED,
    DEEP_EVENT_TYPE_JOYSTICK_DISCONNECTED,
    DEEP_EVENT_TYPE_UNKNOWN,
    ___DEEP_EVENT_TYPE_MAX,
};

typedef struct Deep_Event Deep_Event;
struct Deep_Event
{
    Deep_Event_Type type;
    union
    {
        size_t window;
        Dark_Uuid4 monitor;
        Dark_Uuid4 joystick;
    } id;
    union
    {
        struct
        {
            size_t x;
            size_t y;
        } position;
        struct
        {
            size_t width;
            size_t height;
        } size;
        struct
        {
            double x;
            double y;
        } scroll;
        struct
        {
            Deep_Key key;
            Deep_Key_Modifier modifier;
            int32_t scancode;
        } keyboard;
        struct
        {
            Deep_Mouse_Button button;
            Deep_Key_Modifier modifier;
        } mouse;
        uint32_t codepoint;
        struct
        {
            const char** paths;
            size_t count;
        } file;
        struct
        {
            float x;
            float y;
        } scale;
    } data;
};

#endif // !defined(___DEEP___EVENT_DATA_H)

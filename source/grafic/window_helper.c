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

#include "grafic_module.h"
#include "window_callback.h"
#include "window_helper.h"

#include <dark/core/core.h>

#include <deep/core/core.h>
#include <deep/grafic/grafic.h>
#include <deep/grafic/window_struct.h>

#undef DARK_UNIT
#define DARK_UNIT "window"

int deep_glfw_boolean(const bool b_)
{
    //b_

    if(b_)
    {
        return GLFW_TRUE;
    }
    else
    {
        return GLFW_FALSE;
    }
}

Deep_Key_Modifier deep_window_key_modifier(const int modifier_)
{
    //modifier_

    switch(modifier_)
    {
    case 0:
        return DEEP_KEY_MODIFIER_NONE;
    case GLFW_MOD_SHIFT:
        return DEEP_KEY_MODIFIER_SHIFT;
    case GLFW_MOD_CONTROL:
        return DEEP_KEY_MODIFIER_CONTROLL;
    case GLFW_MOD_ALT:
        return DEEP_KEY_MODIFIER_ALT;
    case GLFW_MOD_SUPER:
        return DEEP_KEY_MODIFIER_SUPER;
    case GLFW_MOD_CAPS_LOCK:
        return DEEP_KEY_MODIFIER_CAPS_LOCK;
    case GLFW_MOD_NUM_LOCK:
        return DEEP_KEY_MODIFIER_NUM_LOCK;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
    }
}

Deep_Key deep_window_key(const int key_)
{
    //key_

    switch(key_)
    {
    case GLFW_KEY_SPACE:
        return DEEP_KEY_SPACE;
    case GLFW_KEY_APOSTROPHE:
        return DEEP_KEY_APOSTROPHE;
    case GLFW_KEY_COMMA:
        return DEEP_KEY_COMMA;
    case GLFW_KEY_MINUS:
        return DEEP_KEY_MINUS;
    case GLFW_KEY_PERIOD:
        return DEEP_KEY_PERIOD;
    case GLFW_KEY_SLASH:
        return DEEP_KEY_SLASH;
    case GLFW_KEY_0:
        return DEEP_KEY_0;
    case GLFW_KEY_1:
        return DEEP_KEY_1;
    case GLFW_KEY_2:
        return DEEP_KEY_2;
    case GLFW_KEY_3:
        return DEEP_KEY_3;
    case GLFW_KEY_4:
        return DEEP_KEY_4;
    case GLFW_KEY_5:
        return DEEP_KEY_5;
    case GLFW_KEY_6:
        return DEEP_KEY_6;
    case GLFW_KEY_7:
        return DEEP_KEY_7;
    case GLFW_KEY_8:
        return DEEP_KEY_8;
    case GLFW_KEY_9:
        return DEEP_KEY_9;
    case GLFW_KEY_SEMICOLON:
        return DEEP_KEY_SEMICOLON;
    case GLFW_KEY_EQUAL:
        return DEEP_KEY_EQUAL;
    case GLFW_KEY_A:
        return DEEP_KEY_A;
    case GLFW_KEY_B:
        return DEEP_KEY_B;
    case GLFW_KEY_C:
        return DEEP_KEY_C;
    case GLFW_KEY_D:
        return DEEP_KEY_D;
    case GLFW_KEY_E:
        return DEEP_KEY_E;
    case GLFW_KEY_F:
        return DEEP_KEY_F;
    case GLFW_KEY_G:
        return DEEP_KEY_G;
    case GLFW_KEY_H:
        return DEEP_KEY_H;
    case GLFW_KEY_I:
        return DEEP_KEY_I;
    case GLFW_KEY_J:
        return DEEP_KEY_J;
    case GLFW_KEY_K:
        return DEEP_KEY_K;
    case GLFW_KEY_L:
        return DEEP_KEY_L;
    case GLFW_KEY_M:
        return DEEP_KEY_M;
    case GLFW_KEY_N:
        return DEEP_KEY_N;
    case GLFW_KEY_O:
        return DEEP_KEY_O;
    case GLFW_KEY_P:
        return DEEP_KEY_P;
    case GLFW_KEY_Q:
        return DEEP_KEY_Q;
    case GLFW_KEY_R:
        return DEEP_KEY_R;
    case GLFW_KEY_S:
        return DEEP_KEY_S;
    case GLFW_KEY_T:
        return DEEP_KEY_T;
    case GLFW_KEY_U:
        return DEEP_KEY_U;
    case GLFW_KEY_V:
        return DEEP_KEY_V;
    case GLFW_KEY_W:
        return DEEP_KEY_W;
    case GLFW_KEY_X:
        return DEEP_KEY_X;
    case GLFW_KEY_Y:
        return DEEP_KEY_Y;
    case GLFW_KEY_Z:
        return DEEP_KEY_Z;
    case GLFW_KEY_LEFT_BRACKET:
        return DEEP_KEY_LEFT_BRACKET;
    case GLFW_KEY_BACKSLASH:
        return DEEP_KEY_BACKSLASH;
    case GLFW_KEY_RIGHT_BRACKET:
        return DEEP_KEY_RIGHT_BRACKET;
    case GLFW_KEY_GRAVE_ACCENT:
        return DEEP_KEY_GRAVE_ACCENT;
    case GLFW_KEY_WORLD_1:
        return DEEP_KEY_WORLD_1;
    case GLFW_KEY_WORLD_2:
        return DEEP_KEY_WORLD_2;
    case GLFW_KEY_ESCAPE:
        return DEEP_KEY_ESCAPE;
    case GLFW_KEY_ENTER:
        return DEEP_KEY_ENTER;
    case GLFW_KEY_TAB:
        return DEEP_KEY_TAB;
    case GLFW_KEY_BACKSPACE:
        return DEEP_KEY_BACKSPACE;
    case GLFW_KEY_INSERT:
        return DEEP_KEY_INSERT;
    case GLFW_KEY_DELETE:
        return DEEP_KEY_DELETE;
    case GLFW_KEY_RIGHT:
        return DEEP_KEY_RIGHT;
    case GLFW_KEY_LEFT:
        return DEEP_KEY_LEFT;
    case GLFW_KEY_DOWN:
        return DEEP_KEY_DOWN;
    case GLFW_KEY_UP:
        return DEEP_KEY_UP;
    case GLFW_KEY_PAGE_UP:
        return DEEP_KEY_PAGE_UP;
    case GLFW_KEY_PAGE_DOWN:
        return DEEP_KEY_PAGE_DOWN;
    case GLFW_KEY_HOME:
        return DEEP_KEY_HOME;
    case GLFW_KEY_END:
        return DEEP_KEY_END;
    case GLFW_KEY_CAPS_LOCK:
        return DEEP_KEY_CAPS_LOCK;
    case GLFW_KEY_SCROLL_LOCK:
        return DEEP_KEY_SCROLL_LOCK;
    case GLFW_KEY_NUM_LOCK:
        return DEEP_KEY_NUM_LOCK;
    case GLFW_KEY_PRINT_SCREEN:
        return DEEP_KEY_PRINT_SCREEN;
    case GLFW_KEY_PAUSE:
        return DEEP_KEY_PAUSE;
    case GLFW_KEY_F1:
        return DEEP_KEY_F1;
    case GLFW_KEY_F2:
        return DEEP_KEY_F2;
    case GLFW_KEY_F3:
        return DEEP_KEY_F3;
    case GLFW_KEY_F4:
        return DEEP_KEY_F4;
    case GLFW_KEY_F5:
        return DEEP_KEY_F5;
    case GLFW_KEY_F6:
        return DEEP_KEY_F6;
    case GLFW_KEY_F7:
        return DEEP_KEY_F7;
    case GLFW_KEY_F8:
        return DEEP_KEY_F8;
    case GLFW_KEY_F9:
        return DEEP_KEY_F9;
    case GLFW_KEY_F10:
        return DEEP_KEY_F10;
    case GLFW_KEY_F11:
        return DEEP_KEY_F11;
    case GLFW_KEY_F12:
        return DEEP_KEY_F12;
    case GLFW_KEY_F13:
        return DEEP_KEY_F13;
    case GLFW_KEY_F14:
        return DEEP_KEY_F14;
    case GLFW_KEY_F15:
        return DEEP_KEY_F15;
    case GLFW_KEY_F16:
        return DEEP_KEY_F16;
    case GLFW_KEY_F17:
        return DEEP_KEY_F17;
    case GLFW_KEY_F18:
        return DEEP_KEY_F18;
    case GLFW_KEY_F19:
        return DEEP_KEY_F19;
    case GLFW_KEY_F20:
        return DEEP_KEY_F20;
    case GLFW_KEY_F21:
        return DEEP_KEY_F21;
    case GLFW_KEY_F22:
        return DEEP_KEY_F22;
    case GLFW_KEY_F23:
        return DEEP_KEY_F23;
    case GLFW_KEY_F24:
        return DEEP_KEY_F24;
    case GLFW_KEY_F25:
        return DEEP_KEY_F25;
    case GLFW_KEY_KP_0:
        return DEEP_KEY_KP_0;
    case GLFW_KEY_KP_1:
        return DEEP_KEY_KP_1;
    case GLFW_KEY_KP_2:
        return DEEP_KEY_KP_2;
    case GLFW_KEY_KP_3:
        return DEEP_KEY_KP_3;
    case GLFW_KEY_KP_4:
        return DEEP_KEY_KP_4;
    case GLFW_KEY_KP_5:
        return DEEP_KEY_KP_5;
    case GLFW_KEY_KP_6:
        return DEEP_KEY_KP_6;
    case GLFW_KEY_KP_7:
        return DEEP_KEY_KP_7;
    case GLFW_KEY_KP_8:
        return DEEP_KEY_KP_8;
    case GLFW_KEY_KP_9:
        return DEEP_KEY_KP_9;
    case GLFW_KEY_KP_DECIMAL:
        return DEEP_KEY_KP_DECIMAL;
    case GLFW_KEY_KP_DIVIDE:
        return DEEP_KEY_KP_DIVIDE;
    case GLFW_KEY_KP_MULTIPLY:
        return DEEP_KEY_KP_MULTIPLY;
    case GLFW_KEY_KP_SUBTRACT:
        return DEEP_KEY_KP_SUBTRACT;
    case GLFW_KEY_KP_ADD:
        return DEEP_KEY_KP_ADD;
    case GLFW_KEY_KP_ENTER:
        return DEEP_KEY_KP_ENTER;
    case GLFW_KEY_KP_EQUAL:
        return DEEP_KEY_KP_EQUAL;
    case GLFW_KEY_LEFT_SHIFT:
        return DEEP_KEY_LEFT_SHIFT;
    case GLFW_KEY_LEFT_CONTROL:
        return DEEP_KEY_LEFT_CONTROL;
    case GLFW_KEY_LEFT_ALT:
        return DEEP_KEY_LEFT_ALT;
    case GLFW_KEY_LEFT_SUPER:
        return DEEP_KEY_LEFT_SUPER;
    case GLFW_KEY_RIGHT_SHIFT:
        return DEEP_KEY_RIGHT_SHIFT;
    case GLFW_KEY_RIGHT_CONTROL:
        return DEEP_KEY_RIGHT_CONTROL;
    case GLFW_KEY_RIGHT_ALT:
        return DEEP_KEY_RIGHT_ALT;
    case GLFW_KEY_RIGHT_SUPER:
        return DEEP_KEY_RIGHT_SUPER;
    case GLFW_KEY_MENU:
        return DEEP_KEY_MENU;
    case GLFW_KEY_UNKNOWN:
        return DEEP_KEY_UNKNOWN;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
    }
}

void deep_window_callback_set(Deep_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    glfwSetWindowPosCallback(window_->instance, deep_window_callback_window_move);
    glfwSetWindowSizeCallback(window_->instance, deep_window_callback_window_resize);
    glfwSetWindowCloseCallback(window_->instance, deep_window_callback_window_close);
    glfwSetWindowRefreshCallback(window_->instance, deep_window_callback_window_refresh);
    glfwSetWindowFocusCallback(window_->instance, deep_window_callback_window_focus);
    glfwSetWindowIconifyCallback(window_->instance, deep_window_callback_window_iconify);
    glfwSetWindowMaximizeCallback(window_->instance, deep_window_callback_window_maximize);
    glfwSetWindowContentScaleCallback(window_->instance, deep_window_callback_window_content_scale);
    glfwSetFramebufferSizeCallback(window_->instance, deep_window_callback_framebuffer_size);
    glfwSetMouseButtonCallback(window_->instance, deep_window_callback_mouse_button);
    glfwSetCursorPosCallback(window_->instance, deep_window_callback_cursor_move);
    glfwSetCursorEnterCallback(window_->instance, deep_window_callback_cursor_enter);
    glfwSetScrollCallback(window_->instance, deep_window_callback_scroll);
    glfwSetKeyCallback(window_->instance, deep_window_callback_key);
    glfwSetCharCallback(window_->instance, deep_window_callback_char);
    glfwSetDropCallback(window_->instance, deep_window_callback_file_drop);
}

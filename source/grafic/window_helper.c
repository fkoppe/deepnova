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

#include <dark/core/core.h>

#include <deep/grafic/grafic.h>

#undef DARK_UNIT
#define DARK_UNIT "window_helper"

int deep_glfw_boolean(const bool b_)
{
    if(b_)
    {
        return GLFW_TRUE;
    }
    else
    {
        return GLFW_FALSE;
    }
}

void deep_window_callback_set(GLFWwindow* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    /*glfwSetWindowPosCallback(window_->instance, dark_window_callback_window_move);
    glfwSetWindowSizeCallback(window_->instance, dark_window_callback_window_resize);
    glfwSetWindowCloseCallback(window_->instance, dark_window_callback_window_close);
    glfwSetWindowRefreshCallback(window_->instance, dark_window_callback_window_refresh);
    glfwSetWindowFocusCallback(window_->instance, dark_window_callback_window_focus);
    glfwSetWindowIconifyCallback(window_->instance, dark_window_callback_window_iconify);
    glfwSetWindowMaximizeCallback(window_->instance, dark_window_callback_window_maximize);
    glfwSetWindowContentScaleCallback(window_->instance, dark_window_callback_window_content_scale);
    glfwSetFramebufferSizeCallback(window_->instance, dark_window_callback_framebuffer_size);
    glfwSetMouseButtonCallback(window_->instance, dark_window_callback_mouse_button);
    glfwSetCursorPosCallback(window_->instance, dark_window_callback_cursor_move);
    glfwSetCursorEnterCallback(window_->instance, dark_window_callback_cursor_enter);
    glfwSetScrollCallback(window_->instance, dark_window_callback_scroll);
    glfwSetKeyCallback(window_->instance, dark_window_callback_key);
    glfwSetCharCallback(window_->instance, dark_window_callback_char);
    glfwSetDropCallback(window_->instance, dark_window_callback_file_drop);*/
}

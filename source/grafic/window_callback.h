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

#if !defined(___DEEP___WINDOW_CALLBACK_H)
#define ___DEEP___WINDOW_CALLBACK_H

#include <dark/core/std.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void deep_window_callback_window_move(GLFWwindow* window, int x, int y);
void deep_window_callback_window_resize(GLFWwindow* window, int width, int height);
void deep_window_callback_window_close(GLFWwindow* window);
void deep_window_callback_window_refresh(GLFWwindow* window);
void deep_window_callback_window_focus(GLFWwindow* window, int focused);
void deep_window_callback_window_iconify(GLFWwindow* window, int iconified);
void deep_window_callback_window_maximize(GLFWwindow* window, int maximized);
void deep_window_callback_window_content_scale(GLFWwindow* window, float xscale, float yscale);
void deep_window_callback_framebuffer_size(GLFWwindow* window, int width, int height);
void deep_window_callback_mouse_button(GLFWwindow* window, int button, int action, int mods);
void deep_window_callback_cursor_move(GLFWwindow* window, double x, double y);
void deep_window_callback_cursor_enter(GLFWwindow* window, int entered);
void deep_window_callback_scroll(GLFWwindow* window, double x, double y);
void deep_window_callback_key(GLFWwindow* window, int key, int scancode, int action, int mods);
void deep_window_callback_char(GLFWwindow* window, unsigned int codepoint);
void deep_window_callback_file_drop(GLFWwindow* window, int count, const char** path);

#endif // !defined(___DEEP___WINDOW_CALLBACK_H)

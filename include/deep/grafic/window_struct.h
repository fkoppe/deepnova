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

#if !defined(___DEEP___WINDOW_STRUCT_H)
#define ___DEEP___WINDOW_STRUCT_H

#include <dark/container/linear_queue_struct.h>
#include <dark/core/std.h>
#include <dark/log/logger.h>
#include <dark/memory/allocator.h>

#include <deep/grafic/window.h>
#include <deep/event/event_queue.h>

#include <GLFW/glfw3.h>

typedef struct Deep_Window_Data Deep_Window_Data;
struct Deep_Window_Data
{
    size_t id;
    Deep_Event_Queue* event_queue;
};

struct Deep_Window
{
    Dark_Allocator* allocator;
    Deep_Window_Settings settings;
    Deep_Window_Data data;
    bool open_is;
    bool fullscreen_is;
    Deep_Window_Option_Array option_array;
    GLFWwindow* instance;
    Dark_Logger* logger;
};

#endif // !defined(___DEEP___WINDOW_STRUCT_H)

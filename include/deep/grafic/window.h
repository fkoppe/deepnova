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

#if !defined(___DEEP___WINDOW_H)
#define ___DEEP___WINDOW_H

#include <dark/core/std.h>
#include <dark/char/cbuffer_view.h>

#include <deep/event/event_queue.h>
#include <deep/grafic/grafic_data.h>
#include <deep/core/monitor.h>

static const Dark_Message DEEP_MESSAGE_WINDOW_OPENED_NOT = { NULL, "window not opened", NULL };
static const Dark_Message DEEP_MESSAGE_WINDOW_OPENED_ALREADY = { NULL, "window already opened", NULL };
static const Dark_Message DEEP_MESSAGE_WINDOW_FULLSCREEN_ALREADY = { NULL, "window already in fullscreen mode", NULL };
static const Dark_Message DEEP_MESSAGE_WINDOW_WINDOWED_ALREADY = { NULL, "window already in windowed mode", NULL };

typedef struct Deep_Window Deep_Window;

typedef enum Deep_Window_Option Deep_Window_Option;
enum Deep_Window_Option
{
    ___DEEP_WINDOW_OPTION_MIN,
    DEEP_WINDOW_OPTION_DECORATE,
    DEEP_WINDOW_OPTION_RESIZE,
    DEEP_WINDOW_OPTION_MAXIMISE,
    DEEP_WINDOW_OPTION_FOCUS,
    DEEP_WINDOW_OPTION_VISIBLE,
    ___DEEP_WINDOW_OPTION_MAX,
};

typedef struct Deep_Window_Option_Array Deep_Window_Option_Array;
struct Deep_Window_Option_Array
{
    bool data[___DEEP_WINDOW_OPTION_MAX];
};

typedef struct Deep_Window_Settings Deep_Window_Settings;
struct Deep_Window_Settings
{
    Dark_Cbuffer_View title;
    struct
    {
        bool is;
        Deep_Grafic_Extend extend;
    } min;
    struct
    {
        bool is;
        Deep_Grafic_Extend extend;
    } max;
};

void deep_window_construct(Dark_Allocator* allocator, Deep_Window* window, size_t id, Deep_Window_Settings settings, Deep_Event_Queue* event_queue, Dark_Logger* logger);
void deep_window_destruct(Deep_Window* window);

Deep_Window* deep_window_new(Dark_Allocator* allocator, size_t id, Deep_Window_Settings settings, Deep_Event_Queue* event_queue, Dark_Logger* logger);
void deep_window_delete(Deep_Window* window);

Deep_Window_Settings deep_window_settings_get(Deep_Window* window);
void deep_window_settings_set(Deep_Window* window, Deep_Window_Settings settings);

bool deep_window_option_is(Deep_Window* window, Deep_Window_Option option);
void deep_window_option_set(Deep_Window* window, Deep_Window_Option option, bool is);
void deep_window_option_array_set(Deep_Window* window, Deep_Window_Option_Array option_array);

void deep_window_open_windowed(Deep_Window* window, Deep_Window_Option_Array option_array, Deep_Grafic_Extend extend);
void deep_window_open_fullscreen(Deep_Window* window, Deep_Window_Option_Array option_array, Deep_Monitor monitor);
bool deep_window_fullscreen_is(Deep_Window* window);

void deep_window_close(Deep_Window* window);
bool deep_window_open_is(Deep_Window* window);

void deep_window_windowed_set(Deep_Window* window, Deep_Grafic_Extend extend);
void deep_window_fullscreen_set(Deep_Window* window, Deep_Monitor monitor);

void deep_window_windowed_resize(Deep_Window* window, Deep_Grafic_Extend extend);
Deep_Grafic_Extend deep_window_windowed_extend(Deep_Window* window);

Deep_Grafic_Extend deep_window_framebuffer_extend(Deep_Window* window);

void deep_window_title_set(Deep_Window* window, Dark_Cbuffer_View title);

size_t deep_window_struct_byte(void);

#endif // !defined(___DEEP___WINDOW_H)

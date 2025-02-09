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
#include "window_helper.h"

#include <dark/container/container.h>
#include <dark/core/core.h>
#include <dark/memory/memory.h>

#include <deep/core/core.h>
#include <deep/event/event.h>
#include <deep/grafic/grafic.h>
#include <deep/grafic/window_struct.h>

#undef DARK_UNIT
#define DARK_UNIT "window"

#define DEEP_ASSERT_WINDOW_SETTINGS(settings) \
DARK_ASSERT((settings).title.data == NULL || (settings).title.size > 0, DARK_ERROR_VALUE); \
DARK_ASSERT(!(settings).min.is || (0 != (settings).min.extend.width && 0 != (settings).min.extend.height), DARK_ERROR_VALUE); \
DARK_ASSERT(!(settings).max.is || (0 != (settings).max.extend.width && 0 != (settings).max.extend.height), DARK_ERROR_VALUE); \
if((settings).min.is && (settings).max.is) \
{ \
    DARK_ASSERT((settings).min.extend.width < (settings).max.extend.width, DARK_ERROR_VALUE); \
    DARK_ASSERT((settings).min.extend.height < (settings).max.extend.height, DARK_ERROR_VALUE); \
}

#define DEEP_ASSERT_WINDOW_EXTEND(settings, ext) \
if((settings).min.is) \
{ \
    DARK_ASSERT((settings).min.extend.width <= (ext).width, DARK_ERROR_VALUE); \
    DARK_ASSERT((settings).min.extend.height <= (ext).height, DARK_ERROR_VALUE); \
} \
if((settings).max.is) \
{ \
    DARK_ASSERT((settings).max.extend.width >= (ext).width, DARK_ERROR_VALUE); \
    DARK_ASSERT((settings).max.extend.height >= (ext).height, DARK_ERROR_VALUE); \
}

void deep_window_construct(Dark_Allocator* const allocator_, Deep_Window* const window_, const size_t id_, const Deep_Window_Settings settings_, Deep_Event_Queue* const event_queue_, Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    //id_
    DEEP_ASSERT_WINDOW_SETTINGS(settings_);
    //event_queue_
    //logger_

    window_->allocator = allocator_;
    window_->settings = settings_;
    window_->self = window_;
    window_->id = id_;
    window_->event_queue = event_queue_;
    window_->open_is = false;
    dark_memset(window_->option_array.data, 0, ___DEEP_WINDOW_OPTION_MAX);
    window_->fullscreen_is = false;
    window_->instance = NULL;
    window_->logger = logger_;
}

void deep_window_destruct(Deep_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    //nothing
}

Deep_Window* deep_window_new(Dark_Allocator* const allocator_, const size_t id_, const Deep_Window_Settings settings_, Deep_Event_Queue* const event_queue_, Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    //id_
    DEEP_ASSERT_WINDOW_SETTINGS(settings_);
    //event_queue_
    //logger_

    Deep_Window* const window = dark_malloc(allocator_, sizeof(*window));
    DARK_ASSERT(NULL != window, DARK_ERROR_ALLOCATION);

    deep_window_construct(allocator_, window, id_, settings_, event_queue_, logger_);

    return window;
}

void deep_window_delete(Deep_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    deep_window_destruct(window_);
}

Deep_Window_Settings deep_window_settings_get(Deep_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    //TODO apply new title

    return window_->settings;
}

void deep_window_settings_set(Deep_Window* const window_, const Deep_Window_Settings settings_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    DEEP_ASSERT_WINDOW_SETTINGS(settings_);

    window_->settings = settings_;
}

bool deep_window_option_is(Deep_Window* const window_, const Deep_Window_Option option_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    DARK_ASSERT(___DEEP_WINDOW_OPTION_MIN < option_ && option_ < ___DEEP_WINDOW_OPTION_MAX, DARK_ERROR_ENUM);

    return window_->option_array.data[option_];
}

void deep_window_option_set(Deep_Window* const window_, const Deep_Window_Option option_, const bool is_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    DARK_ASSERT(___DEEP_WINDOW_OPTION_MIN < option_ && option_ < ___DEEP_WINDOW_OPTION_MAX, DARK_ERROR_ENUM);

    window_->option_array.data[option_] = is_;
}

void deep_window_option_array_set(Deep_Window* const window_, const Deep_Window_Option_Array option_array_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    //option_array

    window_->option_array = option_array_;
}

void deep_window_open_windowed(Deep_Window* const window_, const Deep_Window_Option_Array option_array_, const Deep_Grafic_Extend extend_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    //option_array_
    DEEP_ASSERT_WINDOW_EXTEND(window_->settings, extend_);

    DARK_ASSERT(deep_handler_initialise_is(), DEEP_ERROR_HANDLER_INITIALISED_NOT);

    DARK_ASSERT_MESSAGE(!window_->open_is, DARK_ERROR_STATE, DEEP_MESSAGE_WINDOW_OPENED_ALREADY);

    window_->open_is = true;
    window_->fullscreen_is = false;
    window_->option_array = option_array_;

    glfwWindowHint(GLFW_DECORATED, window_->option_array.data[DEEP_WINDOW_OPTION_DECORATE]);
    glfwWindowHint(GLFW_RESIZABLE, window_->option_array.data[DEEP_WINDOW_OPTION_RESIZE]);
    glfwWindowHint(GLFW_MAXIMIZED, window_->option_array.data[DEEP_WINDOW_OPTION_MAXIMISE]);
    glfwWindowHint(GLFW_FOCUSED, window_->option_array.data[DEEP_WINDOW_OPTION_FOCUS]);

    window_->instance = glfwCreateWindow(extend_.width, extend_.height, window_->settings.title.data, NULL, NULL);
    DARK_ASSERT_CSTRING(NULL != window_->instance, DEEP_ERROR_GLFW, "failed to open window");

    glfwSetWindowUserPointer(window_->instance, window_);

    deep_window_callback_set(window_);

    if (!window_->option_array.data[DEEP_WINDOW_OPTION_VISIBLE])
    {
        glfwHideWindow(window_->instance);
    }

    DARK_IDLOG_CSTRING(window_->logger, window_->id, DARK_LOG_LEVEL_COMMENT, "open windowed");
}

void deep_window_open_fullscreen(Deep_Window* const window_, const Deep_Window_Option_Array option_array_, const Deep_Monitor monitor)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    //option_array_
    //monitor_

    DARK_ASSERT(deep_handler_initialise_is(), DEEP_ERROR_HANDLER_INITIALISED_NOT);

    DARK_ASSERT_MESSAGE(!window_->open_is, DARK_ERROR_STATE, DEEP_MESSAGE_WINDOW_OPENED_ALREADY);

    window_->open_is = true;
    window_->fullscreen_is = false;
    window_->option_array = option_array_;

    const GLFWvidmode* const mode = glfwGetVideoMode(monitor.raw);

    window_->instance = glfwCreateWindow(mode->width, mode->height, window_->settings.title.data, monitor.raw, NULL);
    DARK_ASSERT_CSTRING(NULL != window_->instance, DEEP_ERROR_GLFW, "failed to open window");

    glfwSetWindowUserPointer(window_->instance, window_);

    deep_window_callback_set(window_);

    DARK_IDLOG_CSTRING(window_->logger, window_->id, DARK_LOG_LEVEL_COMMENT, "open windowed");
}

bool deep_window_fullscreen_is(Deep_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_ASSERT(deep_handler_initialise_is(), DEEP_ERROR_HANDLER_INITIALISED_NOT);

    DARK_ASSERT_MESSAGE(window_->open_is, DARK_ERROR_STATE, DEEP_MESSAGE_WINDOW_OPENED_NOT);

    return window_->fullscreen_is;
}

bool deep_window_close_request_is(Deep_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_ASSERT(deep_handler_initialise_is(), DEEP_ERROR_HANDLER_INITIALISED_NOT);

    DARK_ASSERT_MESSAGE(window_->open_is, DARK_ERROR_STATE, DEEP_MESSAGE_WINDOW_OPENED_NOT);

    return glfwWindowShouldClose(window_->instance);
}

void deep_window_close(Deep_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_ASSERT(deep_handler_initialise_is(), DEEP_ERROR_HANDLER_INITIALISED_NOT);

    DARK_ASSERT_MESSAGE(window_->open_is, DARK_ERROR_STATE, DEEP_MESSAGE_WINDOW_OPENED_NOT);
}

bool deep_window_open_is(Deep_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_ASSERT(deep_handler_initialise_is(), DEEP_ERROR_HANDLER_INITIALISED_NOT);

    return window_->open_is;
}

void deep_window_windowed_set(Deep_Window* const window_, const Deep_Grafic_Extend extend_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    DEEP_ASSERT_WINDOW_EXTEND(window_->settings, extend_);

    DARK_ASSERT(deep_handler_initialise_is(), DEEP_ERROR_HANDLER_INITIALISED_NOT);

    DARK_ASSERT_MESSAGE(window_->open_is, DARK_ERROR_STATE, DEEP_MESSAGE_WINDOW_OPENED_NOT);

    DARK_ASSERT_MESSAGE(window_->fullscreen_is, DARK_ERROR_STATE, DEEP_MESSAGE_WINDOW_WINDOWED_ALREADY);

    window_->fullscreen_is = false;

    glfwSetWindowMonitor(window_->instance, NULL, 0, 0, extend_.width, extend_.height, 0);
}

void deep_window_fullscreen_set(Deep_Window* const window_, const Deep_Monitor monitor_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    //monitor_

    DARK_ASSERT(deep_handler_initialise_is(), DEEP_ERROR_HANDLER_INITIALISED_NOT);

    DARK_ASSERT_MESSAGE(window_->open_is, DARK_ERROR_STATE, DEEP_MESSAGE_WINDOW_OPENED_NOT);

    DARK_ASSERT_MESSAGE(!window_->fullscreen_is, DARK_ERROR_STATE, DEEP_MESSAGE_WINDOW_WINDOWED_ALREADY);

    window_->fullscreen_is = true;

    const GLFWvidmode* const mode = glfwGetVideoMode(monitor_.raw);

    glfwSetWindowMonitor(window_->instance, monitor_.raw, 0, 0, mode->width, mode->height, 0);
}

void deep_window_windowed_resize(Deep_Window* const window_, const Deep_Grafic_Extend extend_)
{
    DARK_UNIMPLEMENTED;
}

Deep_Grafic_Extend deep_window_windowed_extend(Deep_Window* window)
{
    DARK_UNIMPLEMENTED;
}

Deep_Grafic_Extend deep_window_framebuffer_extend(Deep_Window* window)
{
    DARK_UNIMPLEMENTED;
}

void deep_window_title_set(Deep_Window* window, Dark_Cbuffer_View title)
{
    DARK_UNIMPLEMENTED;
}

size_t deep_window_struct_byte(void)
{
    return sizeof(Deep_Window);
}

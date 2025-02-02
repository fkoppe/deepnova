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

#include "instance_module.h"
#include "singleton.h"
#include "surface_helper.h"

#include <dark/core/core.h>
#include <dark/memory/memory.h>
#include <dark/random/random.h>

#include <deep/instance/instance.h>

#include "GLFW/glfw3.h"

#undef DARK_UNIT
#define DARK_UNIT "surface"

void deep_surface_monitor_callback(GLFWmonitor* const monitor_, const int event_)
{
    DARK_ASSERT(NULL != monitor_, DARK_ERROR_NULL);
    //event_

    Deep_Surface* const surface = deep_surface_singleton();

    DARK_ASSERT(surface->initialised_is, DARK_ERROR_STATE);

    switch (event_)
    {
    case GLFW_CONNECTED:
        deep_surface_monitor_connect(monitor_);
        break;
    case GLFW_DISCONNECTED:
        deep_surface_monitor_disconnect(monitor_);
        break;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        break;
    }
}

void deep_surface_monitor_connect(GLFWmonitor* const monitor_)
{
    DARK_ASSERT(NULL != monitor_, DARK_ERROR_NULL);

    Deep_Surface* const surface = deep_surface_singleton();

    DARK_ASSERT(surface->initialised_is, DARK_ERROR_STATE);

    Deep_Surface_Data* const data = dark_malloc(surface->allocator, sizeof(Deep_Surface_Data));
    DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

    data->uuid = dark_uuid4_generate(dark_entropy_get_64(surface->entropy));

    glfwSetMonitorUserPointer(monitor_, data);

    Deep_Monitor monitor;
    monitor.name = dark_cstring_to_cbuffer_view(glfwGetMonitorName(monitor_));
    monitor.raw = monitor_;

    if(glfwGetPrimaryMonitor() == monitor_)
    {
        monitor.primary_is = true;
    }

    dark_linear_map_insert(&surface->monitor_map, &data->uuid, &monitor);

    if(NULL != surface->event_queue)
    {
        Deep_Event event;
        event.type = DEEP_EVENT_TYPE_MONITOR_CONNECTED;
        event.id.monitor = data->uuid;

        deep_event_queue_insert(surface->event_queue, event);
    }

    char buffer[DARK_UUID4_SIZE];
    const Dark_Cbuffer cbuffer = { DARK_UUID4_SIZE, buffer };

    dark_uuid4_write(data->uuid, cbuffer);

    DARK_LOG_F(surface->logger, DARK_LOG_LEVEL_COMMENT, "monitor %v connected as %v", dark_cbuffer_to_view(cbuffer), monitor.name);
}

void deep_surface_monitor_disconnect(GLFWmonitor* const monitor_)
{
    DARK_ASSERT(NULL != monitor_, DARK_ERROR_NULL);

    Deep_Surface* const surface = deep_surface_singleton();

    DARK_ASSERT(surface->initialised_is, DARK_ERROR_STATE);

    Deep_Surface_Data* const data = glfwGetMonitorUserPointer(monitor_);
    glfwSetMonitorUserPointer(monitor_, NULL);

    if(NULL != surface->event_queue)
    {
        Deep_Event event;
        event.type = DEEP_EVENT_TYPE_MONITOR_DISCONNECTED;
        event.id.monitor = data->uuid;

        deep_event_queue_insert(surface->event_queue, event);
    }

    char buffer[DARK_UUID4_SIZE];
    const Dark_Cbuffer cbuffer = { DARK_UUID4_SIZE, buffer };

    dark_uuid4_write(data->uuid, cbuffer);

    DARK_LOG_F(surface->logger, DARK_LOG_LEVEL_COMMENT, "monitor %v disconnected", dark_cbuffer_to_view(cbuffer));

    dark_linear_map_erase(&surface->monitor_map, &data->uuid);

    dark_free(surface->allocator, data, sizeof(Dark_Uuid4));
}

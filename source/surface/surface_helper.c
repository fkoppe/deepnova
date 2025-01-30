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
#include "surface_helper.h"

#include <dark/core/core.h>
#include <dark/memory/memory.h>
#include <dark/random/random.h>

#include <deep/instance/instance.h>

#include "GLFW/glfw3.h"

#undef DARK_UNIT
#define DARK_UNIT "surface"

static Deep_Surface DEEP_SURFACE = { .initialised_is = false };

Deep_Surface* deep_surface_singleton(void)
{
    return &DEEP_SURFACE;
}

void deep_surface_monitor_callback(GLFWmonitor* const monitor_, const int event_)
{
    DARK_ASSERT(NULL != monitor_, DARK_ERROR_NULL);
    //event_

    DARK_ASSERT(DEEP_SURFACE.initialised_is, DARK_ERROR_STATE);

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

    DARK_ASSERT(DEEP_SURFACE.initialised_is, DARK_ERROR_STATE);

    Dark_Uuid4* const uuid = dark_malloc(DEEP_SURFACE.allocator, sizeof(Dark_Uuid4));
    DARK_ASSERT(NULL != uuid, DARK_ERROR_ALLOCATION);

    *uuid = dark_uuid4_generate(dark_entropy_get_64(DEEP_SURFACE.entropy));

    glfwSetMonitorUserPointer(monitor_, uuid);

    Deep_Monitor monitor;
    monitor.name = dark_cstring_to_cbuffer_view(glfwGetMonitorName(monitor_));
    monitor.raw = monitor_;

    if(glfwGetPrimaryMonitor() == monitor_)
    {
        monitor.primary_is = true;
    }

    dark_linear_map_insert(&DEEP_SURFACE.monitor_map, uuid, &monitor);

    char buffer[DARK_UUID4_SIZE];
    const Dark_Cbuffer cbuffer = { DARK_UUID4_SIZE, buffer };

    dark_uuid4_write(*uuid, cbuffer);

    DARK_LOG_F(DEEP_SURFACE.logger, DARK_LOG_LEVEL_COMMENT, "monitor %v connected as %v", dark_cbuffer_to_view(cbuffer), monitor.name);
}

void deep_surface_monitor_disconnect(GLFWmonitor* const monitor_)
{
    DARK_ASSERT(NULL != monitor_, DARK_ERROR_NULL);

    DARK_ASSERT(DEEP_SURFACE.initialised_is, DARK_ERROR_STATE);

    Dark_Uuid4* const uuid = glfwGetMonitorUserPointer(monitor_);
    glfwSetMonitorUserPointer(monitor_, NULL);

    char buffer[DARK_UUID4_SIZE];
    const Dark_Cbuffer cbuffer = { DARK_UUID4_SIZE, buffer };

    dark_uuid4_write(*uuid, cbuffer);

    DARK_LOG_F(DEEP_SURFACE.logger, DARK_LOG_LEVEL_COMMENT, "monitor %v disconnected", dark_cbuffer_to_view(cbuffer));

    dark_linear_map_erase(&DEEP_SURFACE.monitor_map, uuid);

    dark_free(DEEP_SURFACE.allocator, uuid, sizeof(Dark_Uuid4));
}

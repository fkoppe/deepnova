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

#include <dark/container/container.h>
#include <dark/core/core.h>
#include <dark/log/log.h>
#include <dark/memory/memory.h>
#include <dark/random/random.h>

#include <deep/instance/instance.h>

#include "GLFW/glfw3.h"

#undef DARK_UNIT
#define DARK_UNIT "surface"

void deep_surface_initialise(Dark_Allocator* const allocator_, Dark_Entropy* const entropy_, Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != entropy_, DARK_ERROR_NULL);
    //logger_

    Deep_Surface* const surface = deep_surface_singleton();

    DARK_ASSERT(!surface->initialised_is, DARK_ERROR_STATE);

    DARK_LOG_MESSAGE_INITIALISE(logger_);

    surface->initialised_is = true;
    surface->allocator = allocator_;
    surface->entropy = entropy_;
    dark_linear_map_construct_capacity(allocator_, &surface->monitor_map, (Dark_Compare)dark_uuid4_compare, sizeof(Dark_Uuid4), sizeof(Deep_Monitor), 1);
    surface->logger = logger_;

    if(!glfwInit())
    {
        DARK_LOG_CSTRING(logger_, DARK_LOG_LEVEL_ERROR, "glfw initialisation failed");
    }

    int count = 0;
    GLFWmonitor** const monitor = glfwGetMonitors(&count);

    if(0 == count)
    {
        DARK_LOG_CSTRING(logger_, DARK_LOG_LEVEL_WARN, "no monitor detected");
    }

    for(size_t i = 0; i < count; i++)
    {
        deep_surface_monitor_connect(monitor[i]);
    }

    glfwSetMonitorCallback(deep_surface_monitor_callback);
}

void deep_surface_shutdown(void)
{
    deep_surface_update();

    Deep_Surface* const surface = deep_surface_singleton();

    DARK_ASSERT(surface->initialised_is, DARK_ERROR_STATE);

    glfwSetMonitorCallback(NULL);

    if(dark_linear_map_size(&surface->monitor_map) > 0)
    {
        Dark_Iterator* const iterator = dark_iterator_new_context(surface->allocator, dark_linear_map_iterator_context_byte());
        deep_surface_monitor_iterator(iterator);

        while (!dark_iterator_done_is(iterator))
        {
            uint8_t* const next = dark_iterator_next(iterator);
            Deep_Monitor* const monitor = (Deep_Monitor*)(next + sizeof(Dark_Uuid4));

            Dark_Uuid4* const uuid = glfwGetMonitorUserPointer(monitor->raw);
            glfwSetMonitorUserPointer(monitor->raw, NULL);

            char buffer[DARK_UUID4_SIZE];
            const Dark_Cbuffer cbuffer = { DARK_UUID4_SIZE, buffer };

            dark_uuid4_write(*uuid, cbuffer);

            DARK_LOG_F(surface->logger, DARK_LOG_LEVEL_COMMENT, "monitor %v removed", dark_cbuffer_to_view(cbuffer));

            dark_free(surface->allocator, uuid, sizeof(Dark_Uuid4));
        }

        dark_iterator_delete(iterator);
    }

    glfwTerminate();

    dark_linear_map_destruct(&surface->monitor_map);

    surface->initialised_is = false;

    DARK_LOG_MESSAGE_SHUTDOWN(surface->logger);
}

void deep_surface_update(void)
{
    Deep_Surface* const surface = deep_surface_singleton();

    DARK_ASSERT(surface->initialised_is, DARK_ERROR_STATE);

    glfwPollEvents();
}

size_t deep_surface_monitor_count(void)
{
    Deep_Surface* const surface = deep_surface_singleton();

    DARK_ASSERT(surface->initialised_is, DARK_ERROR_STATE);

    return dark_linear_map_size(&surface->monitor_map);
}

Deep_Monitor deep_surface_monitor_by_uuid(const Dark_Uuid4 uuid_)
{
    Deep_Surface* const surface = deep_surface_singleton();

    DARK_ASSERT(surface->initialised_is, DARK_ERROR_STATE);

    Deep_Monitor monitor = { false, dark_cstring_to_cbuffer_view("<not connect>") };

    if(dark_linear_map_contain_is(&surface->monitor_map, &uuid_))
    {
        monitor = DARK_LINEAR_MAP_VALUE(&surface->monitor_map, &uuid_, Deep_Monitor);
    }
    else
    {
        char buffer[DARK_UUID4_SIZE];
        const Dark_Cbuffer cbuffer = { DARK_UUID4_SIZE, buffer };

        dark_uuid4_write(uuid_, cbuffer);

        DARK_LOG_F(surface->logger, DARK_LOG_LEVEL_ERROR, "monitor %v is not connected", dark_cbuffer_to_view(cbuffer));
    }

    return monitor;
}

void deep_surface_monitor_iterator(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    Deep_Surface* const surface = deep_surface_singleton();

    DARK_ASSERT(surface->initialised_is, DARK_ERROR_STATE);

    dark_linear_map_iterator(&surface->monitor_map, iterator_);
}

size_t deep_surface_monitor_iterator_context_byte(void)
{
    return dark_linear_map_iterator_context_byte();
}

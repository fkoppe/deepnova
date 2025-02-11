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

#include "core_module.h"
#include "singleton.h"
#include "handler_helper.h"

#include <dark/container/container.h>
#include <dark/core/core.h>
#include <dark/log/log.h>
#include <dark/memory/memory.h>
#include <dark/random/random.h>

#include <deep/core/handler.h>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#undef DARK_UNIT
#define DARK_UNIT "surface"

#include "stdio.h"

void deep_handler_initialise(Dark_Allocator* const allocator_, Dark_Entropy* const entropy_, Deep_Event_Queue* const event_queue_, Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != entropy_, DARK_ERROR_NULL);
    //event_queue_
    //logger_

    Deep_Handler* const handler = deep_handler_singleton();

    DARK_ASSERT(!handler->initialised_is, DARK_ERROR_STATE);

    DARK_LOG_MESSAGE_INITIALISE(logger_);

    handler->initialised_is = true;
    handler->primary_uuid = DARK_UUID4_ZERO;
    handler->allocator = allocator_;
    handler->entropy = entropy_;
    handler->event_queue = event_queue_;
    handler->logger = logger_;

    dark_linear_map_construct_capacity(allocator_, &handler->monitor_map, (Dark_Compare)dark_uuid4_compare, sizeof(Dark_Uuid4), sizeof(Deep_Monitor), 1);

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
        deep_handler_monitor_connect(monitor[i]);
    }

    glfwSetMonitorCallback(deep_handler_monitor_callback);
}

void deep_handler_shutdown(void)
{
    Deep_Handler* const handler = deep_handler_singleton();

    DARK_ASSERT(handler->initialised_is, DARK_ERROR_STATE);

    glfwSetMonitorCallback(NULL);

    if(dark_linear_map_size(&handler->monitor_map) > 0)
    {
        Dark_Iterator* const iterator = dark_iterator_new_context(handler->allocator, dark_linear_map_iterator_context_byte());
        deep_handler_monitor_iterator(iterator);

        while (!dark_iterator_next_is(iterator))
        {
            uint8_t* const next = dark_iterator_next(iterator);
            Deep_Monitor* const monitor = (Deep_Monitor*)(next + sizeof(Dark_Uuid4));

            Deep_Handler_Data* const data = glfwGetMonitorUserPointer(monitor->raw);
            glfwSetMonitorUserPointer(monitor->raw, NULL);

            char buffer[DARK_UUID4_SIZE];
            const Dark_Cbuffer cbuffer = { DARK_UUID4_SIZE, buffer };

            dark_uuid4_write(data->uuid, cbuffer);

            DARK_LOG_F(handler->logger, DARK_LOG_LEVEL_DEBUG, "monitor %v removed", dark_cbuffer_to_view(cbuffer));

            dark_free(handler->allocator, data, sizeof(*data));
        }

        dark_iterator_delete(iterator);
    }

    glfwTerminate();

    dark_linear_map_destruct(&handler->monitor_map);

    handler->initialised_is = false;

    DARK_LOG_MESSAGE_SHUTDOWN(handler->logger);
}

bool deep_handler_initialise_is(void)
{
    Deep_Handler* const handler = deep_handler_singleton();

    return handler->initialised_is;
}

void deep_handler_update(void)
{
    Deep_Handler* const handler = deep_handler_singleton();

    DARK_ASSERT(handler->initialised_is, DARK_ERROR_STATE);

    glfwPollEvents();
}

size_t deep_handler_monitor_count(void)
{
    Deep_Handler* const handler = deep_handler_singleton();

    DARK_ASSERT(handler->initialised_is, DARK_ERROR_STATE);

    return dark_linear_map_size(&handler->monitor_map);
}

Deep_Monitor deep_handler_monitor_primary(void)
{
    Deep_Handler* const handler = deep_handler_singleton();

    DARK_ASSERT(handler->initialised_is, DARK_ERROR_STATE);

    DARK_ASSERT(dark_linear_map_size(&handler->monitor_map) > 0, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT_CSTRING(dark_uuid4_compare(&DARK_UUID4_ZERO, &handler->primary_uuid) != 0, DARK_ERROR_RUNTIME, "no primary monitor");

    return DARK_LINEAR_MAP_VALUE(&handler->monitor_map, &handler->primary_uuid, Deep_Monitor);
}

Deep_Monitor deep_handler_monitor_by_uuid(const Dark_Uuid4 uuid_)
{
    Deep_Handler* const handler = deep_handler_singleton();

    DARK_ASSERT(handler->initialised_is, DARK_ERROR_STATE);

    DARK_ASSERT_CSTRING(dark_linear_map_contain_is(&handler->monitor_map, &uuid_), DARK_ERROR_RUNTIME, "monitor is not connected");

    return DARK_LINEAR_MAP_VALUE(&handler->monitor_map, &uuid_, Deep_Monitor);
}

void deep_handler_monitor_iterator(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    Deep_Handler* const handler = deep_handler_singleton();

    DARK_ASSERT(handler->initialised_is, DARK_ERROR_STATE);

    dark_linear_map_iterator(&handler->monitor_map, iterator_);
}

size_t deep_handler_monitor_iterator_context_byte(void)
{
    return dark_linear_map_iterator_context_byte();
}

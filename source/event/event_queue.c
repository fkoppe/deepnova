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

#include "event_module.h"

#include <dark/container/container.h>
#include <dark/core/core.h>
#include <dark/memory/memory.h>

#include <deep/event/event.h>
#include <deep/event/event_queue_struct.h>

#undef DARK_UNIT
#define DARK_UNIT "event_queue"

static const size_t DEEP_EVENT_QUEUE_SIZE = 1024;

void deep_event_queue_construct(Dark_Allocator* const allocator_, Deep_Event_Queue* const event_queue_, Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != event_queue_, DARK_ERROR_NULL);
    //logger_

    event_queue_->allocator = allocator_;
    dark_linear_queue_construct_capacity(allocator_, &event_queue_->queue, dark_growth_standard, sizeof(*event_queue_), DEEP_EVENT_QUEUE_SIZE);
}

void deep_event_queue_destruct(Deep_Event_Queue* const event_queue_)
{
    DARK_ASSERT(NULL != event_queue_, DARK_ERROR_NULL);

    dark_linear_queue_destruct(&event_queue_->queue);
}

Deep_Event_Queue* deep_event_queue_new(Dark_Allocator* const allocator_, Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    //logger_

    Deep_Event_Queue* const event_queue = dark_malloc(allocator_, sizeof(Deep_Event_Queue));

    deep_event_queue_construct(allocator_, event_queue, logger_);

    return event_queue;
}

void deep_event_queue_delete(Deep_Event_Queue* const event_queue_)
{
    DARK_ASSERT(NULL != event_queue_, DARK_ERROR_NULL);

    deep_event_queue_destruct(event_queue_);

    dark_free(event_queue_->allocator, event_queue_, sizeof(*event_queue_));
}

size_t deep_event_queue_size(Deep_Event_Queue* const event_queue_)
{
    DARK_ASSERT(NULL != event_queue_, DARK_ERROR_NULL);

    return dark_linear_queue_size(&event_queue_->queue);
}

void deep_event_queue_insert(Deep_Event_Queue* const event_queue_, const Deep_Event event_)
{
    DARK_ASSERT(NULL != event_queue_, DARK_ERROR_NULL);

    dark_linear_queue_insert(&event_queue_->queue, &event_);
}

bool deep_event_queue_next_is(Deep_Event_Queue* const event_queue_)
{
    DARK_ASSERT(NULL != event_queue_, DARK_ERROR_NULL);

    return dark_linear_queue_next_is(&event_queue_->queue);
}

Deep_Event deep_event_queue_next(Deep_Event_Queue* const event_queue_)
{
    DARK_ASSERT(NULL != event_queue_, DARK_ERROR_NULL);

    return *(Deep_Event*)dark_linear_queue_next(&event_queue_->queue);
}

void deep_event_queue_clear(Deep_Event_Queue* const event_queue_)
{
    DARK_ASSERT(NULL != event_queue_, DARK_ERROR_NULL);

    dark_linear_queue_clear(&event_queue_->queue);
}

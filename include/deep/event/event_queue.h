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

#if !defined(___DEEP___EVENT_QUEUE_H)
#define ___DEEP___EVENT_QUEUE_H

#include <dark/log/logger.h>
#include <dark/memory/allocator.h>

#include <deep/event/event_data.h>

typedef struct Deep_Event_Queue Deep_Event_Queue;

void deep_event_queue_construct(Dark_Allocator* allocator, Deep_Event_Queue* event_queue, Dark_Logger* logger);
void deep_event_queue_destruct(Deep_Event_Queue* event_queue);

Deep_Event_Queue* deep_event_queue_new(Dark_Allocator* allocator, Dark_Logger* logger);
void deep_event_queue_delete(Deep_Event_Queue* event_queue);

size_t deep_event_queue_size(Deep_Event_Queue* event_queue);

void deep_event_queue_insert(Deep_Event_Queue* event_queue, Deep_Event event);

Deep_Event* deep_event_queue_next(Deep_Event_Queue* event_queue);

void deep_event_queue_clear(Deep_Event_Queue* event_queue);

#endif // !defined(___DEEP___EVENT_QUEUE_H)

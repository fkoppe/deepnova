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

#if !defined(___DEEP___HANDLER_H)
#define ___DEEP___HANDLER_H

#include <dark/core/std.h>
#include <dark/log/logger.h>
#include <dark/memory/allocator.h>
#include <dark/random/entropy.h>
#include <dark/random/uuid4.h>
#include <dark/tool/iterator.h>

#include <deep/core/monitor.h>
#include <deep/event/event_queue.h>

static const Dark_Error DEEP_ERROR_HANDLER_INITIALISED_NOT = { &DARK_ERROR_STATE, "handler not initialised", NULL };

void deep_handler_initialise(Dark_Allocator* allocator, Dark_Entropy* entropy, Deep_Event_Queue* event_queue, Dark_Logger* logger);
void deep_handler_shutdown(void);

bool deep_handler_initialise_is(void);

void deep_handler_update(void);

size_t deep_handler_monitor_count(void);
Deep_Monitor deep_handler_monitor_by_uuid(Dark_Uuid4 uuid);

void deep_handler_monitor_iterator(Dark_Iterator* iterator);
size_t deep_handler_monitor_iterator_context_byte(void);

#endif // !defined(___DEEP___HANDLER_H)

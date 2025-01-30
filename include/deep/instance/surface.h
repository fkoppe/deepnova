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

#if !defined(___DEEP___SURFACE_H)
#define ___DEEP___SURFACE_H

#include <dark/core/std.h>
#include <dark/log/logger.h>
#include <dark/memory/allocator.h>
#include <dark/random/entropy.h>
#include <dark/random/uuid4.h>
#include <dark/tool/iterator.h>

#include <deep/instance/monitor.h>

void deep_surface_initialise(Dark_Allocator* allocator, Dark_Entropy* entropy, Dark_Logger* logger);
void deep_surface_shutdown(void);

void deep_surface_update(void);

size_t deep_surface_monitor_count(void);
Deep_Monitor deep_surface_monitor_by_uuid(Dark_Uuid4 uuid);

void deep_surface_monitor_iterator(Dark_Iterator* iterator);
size_t deep_surface_monitor_iterator_context_byte(void);

#endif // !defined(___DEEP___SURFACE_H)

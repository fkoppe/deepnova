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

#if !defined(___DEEP___INSTANCE_H)
#define ___DEEP___INSTANCE_H

#include <dark/core/std.h>
#include <dark/memory/allocator.h>

typedef struct Deep_Instance Deep_Instance;

void deep_instance_construct(Dark_Allocator* allocator, Deep_Instance* instance);
void deep_instance_destruct(Deep_Instance* instance);

Deep_Instance* deep_instance_new(Dark_Allocator* allocator);
void deep_instance_delete(Deep_Instance* instance);

size_t deep_logger_struct_byte(void);

#endif // !defined(___DEEP___INSTANCE_H)

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

#include "surface_module.h"

#include <dark/core/core.h>
#include <dark/memory/memory.h>

#include <deep/surface/instance_struct.h>
#include <deep/surface/surface.h>

#undef DARK_UNIT
#define DARK_UNIT "instance"

void deep_instance_construct(Dark_Allocator* const allocator_, Deep_Instance* const instance_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != instance_, DARK_ERROR_NULL);

    instance_->allocator = allocator_;
}

void deep_instance_destruct(Deep_Instance* const instance_)
{
    DARK_ASSERT(NULL != instance_, DARK_ERROR_NULL);

    //nothing
}

Deep_Instance* deep_instance_new(Dark_Allocator* const allocator_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Deep_Instance* const instance = dark_malloc(allocator_, sizeof(Deep_Instance));

    deep_instance_construct(allocator_, instance);

    return instance;
}

void deep_instance_delete(Deep_Instance* const instance_)
{
    DARK_ASSERT(NULL != instance_, DARK_ERROR_NULL);

    deep_instance_destruct(instance_);

    dark_free(instance_->allocator, instance_, sizeof(instance_));
}

size_t deep_logger_struct_byte(void)
{
    return sizeof(Deep_Instance);
}

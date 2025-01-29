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

#if !defined(___DEEP___SURFACE_HELPER_H)
#define ___DEEP___SURFACE_HELPER_H

#include <dark/core/std.h>
#include <dark/container/linear_map_struct.h>

#include <deep/instance/surface.h>

#include "GLFW/glfw3.h"

typedef struct Deep_Surface Deep_Surface;
struct Deep_Surface
{
    bool initialised_is;
    Dark_Allocator* allocator;
    Dark_Entropy* entropy;
    Dark_Linear_Map monitor_map;
    Dark_Logger* logger;
};

Deep_Surface* deep_surface_singleton(void);

void deep_surface_monitor_callback(GLFWmonitor* monitor, int event);

void deep_surface_monitor_connect(GLFWmonitor* monitor);
void deep_surface_monitor_disconnect(GLFWmonitor* monitor);

#endif // !defined(___DEEP___SURFACE_HELPER_H)

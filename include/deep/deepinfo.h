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

#if !defined(___DEEP___DEEPINFO_H)
#define ___DEEP___DEEPINFO_H

#include <dark/core/enviroment.h>
#include <dark/core/std.h>
#include <dark/core/version.h>
#include <dark/platform/console.h>

static const Dark_Library DEEP_INFO_LIBRARY_DEEPNOVA = { "deepnova", DARK_VERSION_MAKE(___DEEP_VERSION_MAJOR, ___DEEP_VERSION_MINOR, ___DEEP_VERSION_STAGE, ___DEEP_VERSION_PATCH), ___DARK_CONFIGURATION, DARK_CONSOLE_COLOR_BFG_MAGENTA };

#endif // !defined(___DEEP___DEEPINFO_H)

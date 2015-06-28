/*
  This file is part of libkronos.

  Libkronos is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Libkronos is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with Libkronos.  If not, see <http://www.gnu.org/licenses/>.

  Contributors:
    - Johan Saji <innovatorjohan@gmail.com>

*/

#ifndef KRONOS_CONFIG_H
#define KRONOS_CONFIG_H

#include "kronos_error.h"

KRONOS_RET kronos_processConfig(const char *, const char *);
uint16_t kronos_get_logLevelFromIndex(unsigned int);
uint16_t kronos_get_logLevelFromMod(const char *);
uint8_t kronos_get_indexFromMod(const char *);
char* kronos_get_modFromIndex(unsigned int);
kronos_bool kronos_isLogEnabled();
kronos_bool kronos_isLoggingRequired(const char*, uint8_t);

#endif //KRONOS_CONFIG_H

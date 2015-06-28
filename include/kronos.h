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
#ifndef KRONOS_H
#define KRONOS_H

#include "kronos_error.h"
#include "kronos_loglevels.h"

#ifdef __cplusplus
extern "C"
{
#endif

  KRONOS_RET kronos_init(const char *);

#ifdef DISABLE_LOG
  //Disables logs if DISABLE_LOG is enabled
  #define kronos_log(...)
#else
  void kronos_log(KRONOS_logLevel level, const char * module,
                    const char * message, ...);
#endif

  #define KRONOS_LOG kronos_log

  #define KWARN(module, message, ...) \
      kronos_log(KRONOS_WARNING, module, message, ...)

  #define KERROR(module, message, ...) \
      kronos_log(KRONOS_ERROR, module, message, ...)

  #define KINFO(module, message, ...) \
      kronos_log(KRONOS_INFO, module, message, ...)

#ifdef __cplusplus
}
#endif

#endif // KRONOS_H

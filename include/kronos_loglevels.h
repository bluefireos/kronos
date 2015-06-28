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

#ifndef KRONOS_LOGLEVEL_H
#define KRONOS_LOGLEVEL_H

/******************************************************************************
 * Log format:
 *  {2014-12-24 03:29:51:201 [FATAL][COM.MOD][1000][FUNCTION:123] The actual message goes here.}
 ******************************************************************************/

  typedef enum {
    KRONOS_FATAL    = 0,
    KRONOS_ALERT    = 1,
    KRONOS_CRIT     = 2,
    KRONOS_ERROR    = 3,
    KRONOS_WARNING  = 4,
    KRONOS_NOTICE   = 5,
    KRONOS_INFO     = 6,
    KRONOS_DEBUG    = 7,
    KRONOS_TRACE    = 8,
    KRONOS_LAST_LOG = 9  //Not to be used. Kept there for getting the count
  } KRONOS_logLevel;

#if defined(KRONOS_LOG_STRING)
  const char *kronos_logLevelStrings[] = {
    "FATAL",
    "ALERT",
    "CRITIC",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFO",
    "DEBUG",
    "TRACE",
  };
#endif

#define MAX_LOG_LEVELS KRONOS_LAST_LOG
#define KRONOS_INVALID_LEVEL KRONOS_LAST_LOG

#endif //KRONOS_LOGLEVEL_H

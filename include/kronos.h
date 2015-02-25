#ifndef KRONOS_H
#define KRONOS_H

#include "kronos_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
 * Log format:
 *  {2014-12-24 03:29:51:201 [FATAL][COM.MOD][1000][FUNCTION:123] The actual message goes here.}
 ******************************************************************************/

  typedef enum {
    KRONOS_FATAL = 0,
    KRONOS_ERROR,
    KRONOS_WARNING,
    KRONOS_NOTICE,
    KRONOS_INFO,
    KRONOS_DEBUG,
    KRONOS_TRACE,
    KRONOS_TRACE1,
    KRONOS_TRACE2,
    KRONOS_TRACE3,
  } KRONOS_logLevel;

#if 0
  const char *kronos_logLevelStrings = {
    "KRONOS_FATAL",
    "KRONOS_ERROR",
    "KRONOS_WARNING",
    "KRONOS_NOTICE",
    "KRONOS_INFO",
    "KRONOS_DEBUG",
    "KRONOS_TRACE",
    "KRONOS_TRACE1",
    "KRONOS_TRACE2",
    "KRONOS_TRACE3"
  };
#endif

  KRONOS_RET kronos_init(const char *);

#ifndef DISABLE_LOG
  void kronos_log(KRONOS_logLevel level, const char * module,
                    const char * message, ...);
#else
  #define kronos_log(...)
#endif

  #define KRONOS_LOG kronos_log

#ifdef __cplusplus
}
#endif

#endif // KRONOS_H

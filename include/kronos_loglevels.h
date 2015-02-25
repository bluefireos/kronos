#ifndef KRONOS_LOGLEVEL_H
#define KRONOS_LOGLEVEL_H



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
    KRONOS_LAST_LOG  //Not to be used. Kept there for getting the count
  } KRONOS_logLevel;

#if 1
  const char **kronos_logLevelStrings = {
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

#define MAX_LOG_LEVELS KRONOS_LAST_LOG
#define KRONOS_INVALID_LEVEL KRONOS_LAST_LOG

#endif

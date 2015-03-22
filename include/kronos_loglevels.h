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

#endif

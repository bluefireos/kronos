#ifndef KRONOS_H
#define KRONOS_H

#include "kronos_error.h"

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

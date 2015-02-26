#ifndef KRONOS_H
#define KRONOS_H

#include "kronos_error.h"

#ifdef __cplusplus
extern "C"
{
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

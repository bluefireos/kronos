#ifndef KRONOS_CONFIG_H
#define KRONOS_CONFIG_H

#include "kronos_error.h"

KRONOS_RET kronos_processConfig(const char *, const char *);
unsigned int kronos_get_logLevelFromIndex(unsigned int);
unsigned int kronos_get_logLevelFromMod(const char *);
unsigned int kronos_get_indexFromMod(const char *);

#endif //KRONOS_CONFIG_H

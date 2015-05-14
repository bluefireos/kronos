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

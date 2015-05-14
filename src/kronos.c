/*
 *  Part of BFOS(Elixir) project
 *  Author: Johan Saji
 *  Module: Kronos
 */
#include <stdarg.h>
#include <log4c.h>

#include "kronos_error.h"
#include "kronos_types.h"
#include "kronos_config.h"
#include "kronos.h"

#define DEFAULT_CONFIG "/etc/kronos.conf"
#define DEFAULT_GROUP "kronos"

extern KRONOS_RET kronos_initAppenders();
extern KRONOS_RET kronos_initLayouts();

/*============================================================================*/

static kronos_bool initLogger(){
  if (KRONOS_SUCCESS != kronos_initAppenders()){
    return KRONOS_FAILED;
  }
  if (KRONOS_SUCCESS != kronos_initLayouts()){
    return KRONOS_FAILED;
  }
  return K_TRUE;
}

static KRONOS_RET kronos_logInit(){
  KRONOS_RET ret = KRONOS_FAILED;
  static kronos_bool initialized = K_FALSE;
  if (!initialized){
    initialized = initLogger();
    initialized = K_TRUE;
    log4c_init();
  }

  return ret;
}

static kronos_bool isLogRequired(const char *module, KRONOS_logLevel level){
  return kronos_isLoggingRequired(module, level); 
}

static log4c_category_t* cachedCategory[100] = {NULL};

static void log_message(KRONOS_logLevel level, const char * module,
    const char *format, va_list message){
  int moduleIndex = kronos_get_indexFromMod(module);
  
  if(K_FALSE == isLogRequired(module, level)){
    return;
  }
  if(NULL == cachedCategory[moduleIndex]){
    cachedCategory[moduleIndex] = log4c_category_get(module);
  }

  log4c_category_log(cachedCategory[moduleIndex], (level * 100), format, message);
}

/*============================================================================*/
/*
 * kronos public api
 * To be called before using any other api
 */
KRONOS_RET kronos_init(const char *config_file){
  KRONOS_RET ret = KRONOS_FAILED;
  
  if (NULL == config_file){
    config_file = DEFAULT_CONFIG;
  }
  ret = kronos_processConfig(config_file, DEFAULT_GROUP);
  if (KRONOS_FAILED == ret){
    fprintf(stderr, "Error processing coniguration file %s", config_file);
    return ret;
  }
  ret = kronos_logInit();
  return ret;
}

void  kronos_log(KRONOS_logLevel level, const char * module,
    const char * message, ...){
  va_list args;
  va_start(args, message);

  if(kronos_isLogEnabled()){
      if (level <= kronos_get_logLevelFromMod(module)){
        log_message(level, module, message, args);
      }
  }
  va_end(args);
}

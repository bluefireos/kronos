/*
 *  Part of BFOS(Elixir) project
 *  Author: Johan Saji
 *  Module: Kronos
 */
#include <log4c.h>

#include "kronos_error.h"
#include "kronos_types.h"
#include "kronos_config.h"
#include "kronos.h"

#define DEFAULT_CONFIG "/etc/kronos.conf"
#define DEFAULT_GROUP "kronos"


/*============================================================================*/
KRONOS_RET kronos_logInit(){
  KRONOS_RET ret = KRONOS_FAILED;
  static kronos_bool initialized = K_FALSE;
  if (!initialized){
    initialized = initLogger();
  }

  return ret;
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

void kronos_log(KRONOS_logLevel level, const char * module,
                const char * message, ...){
                
}

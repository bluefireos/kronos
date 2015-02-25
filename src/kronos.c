
#include <log4c.h>

#include "logger_pvt.h"
#include "kronos_error.h"
#include "kronos_types.h"
#include "kronos_config.h"
#include "kronos.h"

#define DEFAULT_CONFIG "/etc/kronos.conf"


/*============================================================================*/
KRONOS_RET kronos_logInit(){
  KRONOS_RET ret;
  static kronos_bool initialized = FALSE;
  if (!initialized){
    initialized = initLogger();
  }
}




/*============================================================================*/
/*
 * kronos public api
 * To be called before using any other api
 */
KRONOS_RET kronos_init(const char *config_file){
  KRONOS_RET ret;
  
  if (NULL == config_file){
    config_file = DEFAULT_CONFIG;
  }
  ret = kronos_processConfig(config_file);
  if (KRONOS_FAILED == ret){
    fprintf(stderr, "Error processing coniguration file %s", config_file);
    return;
  }
  ret = kronos_logInit();
}

void kronos_log(KRONOS_logLevel level, const char * module,
                const char * message, ...){
                
}

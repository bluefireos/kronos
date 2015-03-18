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
    printf("log4c init\n");
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

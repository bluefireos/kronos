
#define DEFAULT_LOG_DIR ./

static int kronos_appender_open(log4c_appender_t* this){
}


static const log4c_appender_type_t log4c_kronos_appender = 
    { "kronos_appender", kronos_appender_open, kronos_appender_append,
    kronos_appender_close };



/*============================================================================*/
/*
 * If you want to add another appender add it here
 */
static const log4c_appender_type_t *log4c_kronos_appenders[] = {
    &log4c_kronos_appender
    };


KRONOS_RET kronos_initAppenders(){
  int i = 0;
  int nAppenders = (int)(sizeof(log4c_kronos_appenders)/
                         sizeof(log4c_kronos_appenders[0]));

  for (i = 0; i<nAppenders; i++){
    (void) log4c_appender_type_set(log4c_kronos_appenders[i]);
  }
  return KRONOS_SUCCESS;
}



static int kronos_appender_open(log4c_appender_t* appender){
  
}


static const log4c_appender_type_t
    log4c_kronos_appender =
    { "kronos_appender", kronos_appender_open, kronos_appender_append,
    kronos_appender_close, };



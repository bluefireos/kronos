/*
 *  Part of BFOS(Elixir) project
 *  Author: Johan Saji
 *  Module: Kronos
 */

#include <string.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <time.h>
#include <log4c/layout.h>
#include "kronos_error.h"

static const char* kronos_default_format(const log4c_layout_t* a_layout,
    const log4c_logging_event_t*a_event){
  struct tm time;
  
  pid_t threadID = syscall(SYS_gettid);
  gmtime_r(&a_event->evt_timestamp.tv_sec, &time);
  //[YYYY:MM:DD HH:MM:SS][FATAL][COM.MOD][TID][FUNCTION:123] The actual message goes here.
  snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size,
      "[%04d:%02d:%02d %02d:%02d:%02d][%-5d][%s][%d]%s",
      time.tm_year, time.tm_mon, time.tm_mday, time.tm_hour, time.tm_min,
      time.tm_sec, log4c_priority_to_string(a_event->evt_priority),
      a_event->evt_category, threadID, a_event->evt_msg);

  return a_event->evt_buffer.buf_data;  
}

static const log4c_layout_type_t kronos_layout = {
    "kronos_layout", kronos_default_format};

/*============================================================================*/
/*
 * If you want to add another appender add it here
 */
static const log4c_layout_type_t *log4c_kronos_layouts[] = {
    &kronos_layout
    };


KRONOS_RET kronos_initLayouts(){
  int i = 0;
  int nLayouts = (int)(sizeof(log4c_kronos_layouts)/
                         sizeof(log4c_kronos_layouts[0]));

  for (i = 0; i < nLayouts; i++){
    (void) log4c_layout_type_set(log4c_kronos_layouts[i]);
  }
  return KRONOS_SUCCESS;
}

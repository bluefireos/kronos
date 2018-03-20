/*
  This file is part of libkronos.

  Contributors:
    - Johan Saji <johansaji.dev@gmail.com>

*/

#include <string.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <time.h>
#include <log4c.h>
#include <log4c/layout.h>
#include "kronos_loglevels.h"
#include "kronos_error.h"

#define YEAR_OFFSET 1900
#define MONTH_OFFSET 1


static const char* kronos_color_format(const log4c_layout_t* a_layout,
    const log4c_logging_event_t*a_event){
  struct tm time; 
  pid_t threadID = syscall(SYS_gettid);
  gmtime_r(&a_event->evt_timestamp.tv_sec, &time);

  switch(a_event->evt_priority/100){
    case KRONOS_FATAL:
    case KRONOS_ALERT:
    case KRONOS_CRIT:
    case KRONOS_ERROR:
      snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size,
          "\x1b[31m[%04d:%02d:%02d %02d:%02d:%02d][%s][%d]%s\x1b[0m\n",
          time.tm_year + YEAR_OFFSET, time.tm_mon + MONTH_OFFSET, time.tm_mday, 
          time.tm_hour, time.tm_min, time.tm_sec,
          a_event->evt_category, threadID, a_event->evt_msg);
      break;
    case KRONOS_WARNING:
    case KRONOS_NOTICE:
      snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size,
          "\x1b[35m[%04d:%02d:%02d %02d:%02d:%02d][%s][%d]%s\x1b[0m\n",
          time.tm_year + YEAR_OFFSET, time.tm_mon + MONTH_OFFSET, time.tm_mday, 
          time.tm_hour, time.tm_min, time.tm_sec, 
          a_event->evt_category, threadID, a_event->evt_msg);
      break;
    default:
      snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size,
          "[%04d:%02d:%02d %02d:%02d:%02d][%s][%d]%s\n",
          time.tm_year + YEAR_OFFSET, time.tm_mon + MONTH_OFFSET, time.tm_mday, 
          time.tm_hour, time.tm_min, time.tm_sec, 
          a_event->evt_category, threadID, a_event->evt_msg);
      break;
  }
  return a_event->evt_buffer.buf_data;  
}

static const char* kronos_default_format(const log4c_layout_t* a_layout,
    const log4c_logging_event_t*a_event){
  struct tm time;
  
  pid_t threadID = syscall(SYS_gettid);
  gmtime_r(&a_event->evt_timestamp.tv_sec, &time);
  //[YYYY:MM:DD HH:MM:SS][FATAL][COM.MOD][TID][FUNCTION:123] The actual message goes here.
  snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size,
      "[%04d:%02d:%02d %02d:%02d:%02d][%-5s][%s][%d]%s",
      time.tm_year + YEAR_OFFSET, time.tm_mon + MONTH_OFFSET, time.tm_mday, 
      time.tm_hour, time.tm_min, time.tm_sec, 
      log4c_priority_to_string(a_event->evt_priority),
      a_event->evt_category, threadID, a_event->evt_msg);

  return a_event->evt_buffer.buf_data;  
}

static const log4c_layout_type_t kronos_layout = {
    "kronos_layout", kronos_default_format};
static const log4c_layout_type_t kronos_color_layout = {
    "kronos_color_layout", kronos_color_format};

/*============================================================================*/
/*
 * If you want to add another appender add it here
 */
static const log4c_layout_type_t *log4c_kronos_layouts[] = {
    &kronos_layout,
    &kronos_color_layout
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

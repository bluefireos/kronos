#include <stdio.h>

 #define _GNU_SOURCE
        #include <unistd.h>
               #include <sys/syscall.h>

#include <log4c.h>
#include <log4c/appender.h>
#include <sys/types.h>


static const char* dated_format_nocr(const log4c_layout_t* a_layout,
        const log4c_logging_event_t*a_event){
  snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size, "<<%s>>[%-8s][%ld] %s",
  log4c_priority_to_string(a_event->evt_priority), a_event->evt_category, syscall(SYS_gettid),
                     a_event->evt_msg);
  return   a_event->evt_buffer.buf_data;
}

static const log4c_layout_type_t log4c_layout_type_dated_nocr =
{ "dated_nocr", dated_format_nocr, };

int test_open   (log4c_appender_t* this){
  printf("%s\n", __FUNCTION__);
  printf("0---> %s\n", log4c_appender_get_name(this));
  FILE* fp = log4c_appender_get_udata(this);
  if (fp)
    return 0;
  fp = fopen(log4c_appender_get_name(this), "a+");
  setbuf(fp, NULL);
  log4c_appender_set_udata(this, fp);
  return 0;
}

int test_append (log4c_appender_t* this, const log4c_logging_event_t* event){
  printf("%s\n", __FUNCTION__);
  FILE* fp = log4c_appender_get_udata(this);
  //printf ("%s", event->evt_rendered_msg);
  return fprintf(fp, "%s\n",event->evt_rendered_msg);
  return 0;
}

int test_close  (log4c_appender_t* this){
  printf("%s\n", __FUNCTION__);
  FILE* fp = log4c_appender_get_udata(this);
  
  return fp ? close(fp): 0;
}

static const log4c_appender_type_t my_appender = {
      "test_appender", &test_open, test_append, test_close
    };


int main(){
  log4c_category_t* mycat = NULL;
  printf("%s %ld\n", __FUNCTION__, syscall(SYS_gettid));
  (void) log4c_appender_type_set(&my_appender); 
  (void) log4c_layout_type_set(&log4c_layout_type_dated_nocr);
  log4c_init();
  mycat = log4c_category_get("test.jim");
  if(mycat == NULL){
    printf("NULL\n");
  }
  log4c_category_log(mycat, LOG4C_PRIORITY_ERROR, "Debugging app 1 - loop");

   /* Explicitly call the log4c cleanup routine */
     if ( log4c_fini()){
         printf("log4c_fini() failed");
           }

  return 0;
}

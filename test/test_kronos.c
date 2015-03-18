#include <stdio.h>
#include <log4c.h>
#include <log4c/appender.h>
#include <kronos.h>

int main(){
  log4c_category_t* mycat = NULL;
  kronos_init("./kronos.conf");
   mycat = log4c_category_get("test.jim");
    log4c_category_log(mycat, LOG4C_PRIORITY_ERROR, "Debugging app 1 - loop");
    log4c_fini();
return 0;
}

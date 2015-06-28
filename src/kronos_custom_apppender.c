/*
  This file is part of libkronos.

  Libkronos is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Libkronos is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with Libkronos.  If not, see <http://www.gnu.org/licenses/>.

  Contributors:
    - Johan Saji <innovatorjohan@gmail.com>

*/

#include <stdlib.h>
#include <string.h>
#include <log4c/appender.h>
#include "kronos_error.h"


#define DEFAULT_LOG_DIR "./"

static int kronos_appender_open(log4c_appender_t* this){
  char *logFileName = NULL;
  FILE *fp = (FILE *)log4c_appender_get_udata(this);
  if (fp){
    return 0;
  }
  
  logFileName = strdup(log4c_appender_get_name(this));
//  logFileName = strcat(DEFAULT_LOG_DIR, logFileName);

  fp = fopen(logFileName, "w");
  if (NULL == fp){
    fprintf(stderr,"Unable to open the Logfile %s ....\n", logFileName);
    fp = stderr;
  }

  setbuf(fp, NULL);
  log4c_appender_set_udata(this, fp);
  free(logFileName);
  return 0;
}

static int kronos_appender_append(log4c_appender_t* this, 
     const log4c_logging_event_t* event){
  FILE *fp = (FILE *)log4c_appender_get_udata(this);
  fprintf(fp, "%s\n",event->evt_rendered_msg);
  fflush(fp);
  return 0;
}

static int kronos_appender_close(log4c_appender_t* this){
  FILE *fp = (FILE *)log4c_appender_get_udata(this);
  return fp ? fclose(fp) : 0;
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

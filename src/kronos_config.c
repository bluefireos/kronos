
#include <stdio.h>
#include <string.h>

#include "kronos_error.h"
#include "kronos_types.h"
#include "kronos_config.h"

#define MAX_BUFFER_SIZE 128

typedef struct ConfigNode{
  unsigned int index;
  char *mod;
  unsigned int logLevel;
  struct ConfigNode *next;
} ConfigNode;

static pthread_mutex_t configMutex = PTHREAD_MUTEX_INITIALIZER;
static configNode *config = NULL;

KRONOS_RET kronos_processConfig(const char *configFile){
  ConfigNode *node = config;
  FILE *fp = NULL;
  char readBuffer[MAX_BUFFER_SIZE];
  unsigned int bufferLength = 0;
  int i = 0;
  
  fp = fopen(configFile, "r");
  if (NULL == fp){
    fprintf(stderr, "Unable to load %s...", configFile);
    return KRONOS_FAILED;
  }

  pthread_mutex_lock(&configMutex);
  while (EOF != fgets(readBuffer, MAX_BUFFER_SIZE, fp)){
    char *equals = NULL;

    // neglect lines starting with '#' and ';'
    if ('#' == readBuffer[0])
      continue;
    if (';' == readBuffer[0])
      continue;
    // neglect line without '='
    if (NULL == (equals = strchr(readBuffer, '=')))
      continue;
    



  }
  pthread_mutex_unlock(&configMutex);
}

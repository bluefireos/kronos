/*
  This file is part of libkronos.

  Contributors:
    - Johan Saji <johansaji.dev@gmail.com>

*/

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include <stdint.h>

#include "kronos_error.h"
#include "kronos_types.h"
//#define KRONOS_LOG_STRING
#include "kronos_loglevels.h"
#include "kronos_config.h"

#define MAX_BUFFER_SIZE 128

#define list_for_each(pos, head)           \
  for (pos = head; NULL != pos; pos = pos->next)

typedef struct ConfigNode{
  unsigned int index;
  char *mod;
  uint16_t logLevel;
  struct ConfigNode *next;
} ConfigNode;

static kronos_bool logEnabled = K_FALSE;

static pthread_mutex_t configMutex = PTHREAD_MUTEX_INITIALIZER;
static ConfigNode *m_config = NULL;


static void dump_nodes( ConfigNode *head){
  while (NULL != head){
    printf("%d %-7s %x\n", head->index, head->mod, head->logLevel);
    head = head->next; 
  }
}

#if 0
static char *firstChar(char *logString){
  char *startPointer = logString;
  while (' ' == *startPointer){
    startPointer++;
  }
  return startPointer;
}
#endif

static char *endChar(char *logString){
  int length = strlen(logString);
  char *startPointer = logString;
  char *endPointer = logString + length - 1;
  if (0 == length){
    return NULL;
  }

  while(' ' == *endPointer || '\0' == *endPointer){
    if(endPointer == startPointer)
      return NULL;
    endPointer--;
  }
  return endPointer;
}

static uint16_t processLogLevel(char* logString){
  char *traversePointer;
  char *endPointer;
  uint16_t logLevel = 0;

  traversePointer = logString;
  endPointer = endChar(traversePointer);
  while(endPointer > traversePointer){
    int i = 0;
    int word_length;
    char *space = strchr(traversePointer, ' ');
    if(NULL == space){
      space = endPointer + 1;
    }
    word_length = space - traversePointer;
    if( 4 > word_length){
      traversePointer = space + 1;
      continue;
    }
    while (i < MAX_LOG_LEVELS){
      //Checking for log-Levels for different modules
      if (!strncasecmp(traversePointer, kronos_logLevelStrings[i], word_length)){
        logLevel |= (1 << i);
      }
      i++;
    }
    traversePointer = space + 1;
  }

  return logLevel;
}

static uint16_t get_logLevel(GKeyFile *configFile, const char *group,
                gchar *key){
  GError *error = NULL;
  char *value = NULL;

  value = g_key_file_get_value(configFile, group, key, &error);
  if (NULL == value){
    return KRONOS_INVALID_LEVEL;
  }
    //checking for the global flag enableLog
  if (!strcmp(key, "enableLog")){
    if(!strcasecmp(value, "TRUE")){
      logEnabled = K_TRUE;
      return 1;
    }
    else if(!strcasecmp(value, "FALSE"))
      return 0;
    else
      return KRONOS_INVALID_LEVEL;
  }
 
  return processLogLevel(value);
#if 0
  while (i < MAX_LOG_LEVELS){

    //Checking for log-Levels for different modules
    if (!strcasecmp(value, kronos_logLevelStrings[i])){
      return i;
    }
    i++;
  }
  
  return KRONOS_INVALID_LEVEL;
#endif
}

static ConfigNode *get_config(GKeyFile *configFile, const char *group, 
                      gchar **keys, gsize size){
  gsize i = 0;
  ConfigNode *nodes = NULL;
  while(size > i){
    ConfigNode *node = (ConfigNode *)malloc(sizeof(ConfigNode));
    node->index = i;
    node->mod = strdup(keys[i]);
    
    node->logLevel = get_logLevel(configFile, group, keys[i]);
    // Adding new node to the begining of the list
    node->next = nodes;
    nodes = node;
    i++;
  }
  return nodes;
}

/*---------------------------- Public Functions ------------------------------*/

uint8_t kronos_get_indexFromMod(const char *mod){
  ConfigNode *node = NULL;
  list_for_each(node, m_config){
    if(!strcasecmp(mod, node->mod)){
      return node->index;    
      }
  }
  return 0;
}

uint16_t kronos_get_logLevelFromMod(const char *mod){
  ConfigNode *node = NULL;
  list_for_each(node, m_config){
    if(!strcasecmp(mod, node->mod)){
      return node->logLevel;
    }
  }
  return KRONOS_INVALID_LEVEL;
}

uint16_t kronos_get_logLevelFromIndex(unsigned int index){
  ConfigNode *node = NULL;
  list_for_each(node, m_config){
    if (node->index == index){
      return node->logLevel;
    }
  }
  return KRONOS_INVALID_LEVEL;
}

char* kronos_get_modFromIndex(unsigned int index){
  ConfigNode *node = NULL;
  list_for_each(node, m_config){
    if (node->index == index){
      return node->mod;
    }
  }
  return NULL;
}

KRONOS_RET kronos_processConfig(const char *configFile, const char *group){
  GKeyFile *confFile = NULL;
  GError *error = NULL;
  gchar **keys = NULL;
  gsize size = 0;

  confFile = g_key_file_new();
  pthread_mutex_lock(&configMutex);

  if (!g_key_file_load_from_file(confFile, configFile,
                  G_KEY_FILE_NONE, &error)){
    fprintf(stderr, "%s", error->message);
    return KRONOS_FAILED;
  }
  keys = g_key_file_get_keys(confFile, group, &size, &error);
  if (NULL == keys){
    fprintf(stderr, "%s", error->message);
    g_key_file_free(confFile);
    return KRONOS_FAILED;
  }
  m_config = get_config(confFile, group, keys, size);
  //dump_nodes(m_config);

  g_strfreev(keys);
  g_key_file_free(confFile);
  pthread_mutex_unlock(&configMutex);
  return KRONOS_SUCCESS;
}

kronos_bool kronos_isLogEnabled(){
  return logEnabled;
}

kronos_bool kronos_isLoggingRequired(const char* module, uint8_t level){
  uint16_t logLevel = kronos_get_logLevelFromMod(module);
  
  return (logLevel & (1 << level)) ? K_TRUE:K_FALSE;
}

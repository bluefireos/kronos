
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "kronos_error.h"
#include "kronos_types.h"
//#include "kronos_list.h"
#include "kronos_loglevels.h"
#include "kronos_config.h"

#define MAX_BUFFER_SIZE 128

#define list_for_each(pos, head)           \
  for (pos = head; NULL != pos; pos = pos->next)

typedef struct ConfigNode{
  unsigned int index;
  char *mod;
  unsigned int logLevel;
  struct ConfigNode *next;
} ConfigNode;

static pthread_mutex_t configMutex = PTHREAD_MUTEX_INITIALIZER;
static ConfigNode *m_config = NULL;


static void dump_nodes( ConfigNode *head){
  while (NULL != head){
    printf("%d %-7s %d\n", head->index, head->mod, head->logLevel);
    head = head->next; 
  }
}


static unsigned int get_logLevel(GKeyFile *configFile, const char *group,
                gchar *key){
  GError *error = NULL;
  char *value = NULL;
  int i = 0;

  value = g_key_file_get_value(configFile, group, key, &error);
  if (NULL == value){
    return KRONOS_INVALID_LEVEL;
  }
  
  while (i < MAX_LOG_LEVELS){
    //checking for the global flag enableLog
    if (!strcmp(key, "enableLog")){
      if(!strcasecmp(value, "TRUE"))
        return 1;
      else if(!strcasecmp(value, "FALSE"))
        return 0;
      else
        return KRONOS_INVALID_LEVEL;
    }

    //Checking for log-Levels for different modules
    if (!strcasecmp(value, kronos_logLevelStrings[i])){
      return i;
    }
    i++;
  }
  
  return KRONOS_INVALID_LEVEL;
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

/*----------------------------------------------------------------------------*/

unsigned int kronos_get_indexFromMod(const char *mod){
  ConfigNode *node = NULL;
  list_for_each(node, m_config){
    if(!strcasecmp(mod, node->mod)){
      return node->index;    
      }
  }
  return 0;
}
unsigned int kronos_get_logLevelFromMod(const char *mod){
  ConfigNode *node = NULL;
  list_for_each(node, m_config){
    if(!strcasecmp(mod, node->mod)){
      return node->logLevel;
    }
  }
  return KRONOS_INVALID_LEVEL;
}

unsigned int kronos_get_logLevelFromIndex(unsigned int index){
  ConfigNode *node = NULL;
  list_for_each(node, m_config){
    if (node->index == index){
      return node->logLevel;
    }
  }
  return KRONOS_INVALID_LEVEL;
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
  dump_nodes(m_config);

  g_strfreev(keys);
  g_key_file_free(confFile);
  pthread_mutex_unlock(&configMutex);
  return KRONOS_SUCCESS;
}

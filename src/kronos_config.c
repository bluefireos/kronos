
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>

#include "kronos_error.h"
#include "kronos_types.h"
#include "kronos_loglevels.h"
#include "kronos_config.h"

#define MAX_BUFFER_SIZE 128

typedef struct ConfigNode{
  unsigned int index;
  char *mod;
  unsigned int logLevel;
  struct ConfigNode *next;
} ConfigNode;

static pthread_mutex_t configMutex = PTHREAD_MUTEX_INITIALIZER;
static ConfigNode *config = NULL;


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
      printf("#########\n");
    if (0 == strcmp(value, kronos_logLevelStrings[i])){
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
    printf("$$$$$$$\n");
    
    node->logLevel = get_logLevel(configFile, group, keys[i]);

    // Adding new node to the begining of the list
    node->next = nodes;
    nodes = node;
    i++;
  }
  return nodes;
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
  config = get_config(confFile, group, keys, size);
  dump_nodes(config);

  g_strfreev(keys);
  g_key_file_free(confFile);
  pthread_mutex_unlock(&configMutex);
}

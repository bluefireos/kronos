//gcc -g  config_test.c ../src/kronos_config.c -I../include/ -I../../rootfs/fs/include/glib-2.0/ -I../../rootfs/fs/lib/glib-2.0/include/ -L../../rootfs/fs/lib/glib-2.0/ -lglib-2.0

#include <stdio.h>

#include "kronos_config.h"

int main(int argc, char **argv){
  kronos_processConfig(argv[1], "kronos");
  return 0;
}

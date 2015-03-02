
include ../Makefile.config


types: types_test.cpp 
	$(CC) $^ -o ../$(TEST_DIR)/$@ -I../include $(CFLAGS)

config: config_test.c
	$(CC) $^ ../src/kronos_config.c -I../include/ -I$(ROOTFS)/include/glib-2.0/ -I$(ROOTFS)/lib/glib-2.0/include/ -L$(ROOTFS)/lib/ -lglib-2.0 $(CFLAGS)

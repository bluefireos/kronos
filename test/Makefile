include ../Makefile.conf


SRC_DIR    = ./
INC_DIR    = ./

SRCS       = config_test.c  \
             test_appender.c  \
             test_kronos.c

KRONOS_LIB = -L../build/lib -lkronos
KRONOS_INC = -I../include

################################################################################
INCLUDE   += $(KRONOS_INC)
LFLAGS    += $(KRONOS_LIB)

all: kronos_test
	@echo "--- $^ Build completed ---"
	@echo "For rebuilding :-  make clean && make"

kronos_test: test_kronos.c
	@echo "[CC] Building $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(INCLUDE) $(LFLAGS) $(KRONOS_LIB)

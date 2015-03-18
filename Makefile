include Makefile.conf

CC         = $(TOOLCHAIN)$(CC_PREFIX)gcc$(CC_SUFIX)
STRIP      = $(TOOLCHAIN)/$(CC_PREFIX)strip$(CC_SUFIX)

SRC_DIR    = ./src
INC_DIR    = ./include
LIBRARY    = $(LIB_DIR)/$(LIB_NAME)

SRCS       = kronos_config.c  \
             kronos_custom_apppender.c  \
             kronos_custom_layout.c \
             kronos.c

SOURCES   := $(foreach SRC, $(SRCS), $(SRC_DIR)/$(SRC))
INCLUDES  := $(wildcard $(INC_DIR)/*.h)
OBJECTS   := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIRS      := $(LIB_DIR) $(OBJ_DIR) $(ENV_DIR) $(TEST_DIR)

################################################################################

all: $(OBJ_DIR) $(LIBRARY)
	@echo "--- $(LIB_NAME) Build completed ---"
	@echo "For rebuilding :-  make clean && make"

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "[CC] $@ ..."
	@$(CC) -c $^ $(CFLAGS) -I$(INC_DIR) $(INCLUDE) -o $@ 

$(DIRS):
	@echo "Creating $@"
	mkdir -p $(DIRS)

clean:
	@echo "[RM] $(OBJECTS) ..."
	@rm -f $(OBJECTS)

distclean:
	@echo "[RM] $(DIRS) ..."
	@rm -rf $(DIRS)

$(LIBRARY): $(OBJECTS)
	@echo "[LD] $(OBJECTS)"
	@$(CC) $(OBJECTS) $(LFLAGS) $(LIBS_PATHS) -o $@
	@ln -s $(LIB_NAME)  $(SOFT_NAME)
	@mv $(SOFT_NAME) $(LIB_DIR)


include Makefile.config

.PHONY: test


all: $(LIB_DIR)
	@echo $(LIB_NAME)

test:
	make -C test


$(LIB_DIR):
	@echo "Configuring output dir..."
	@mkdir -p $(LIB_DIR)
	@ln -s $(LIB_NAME) $(SOFT_NAME)
	@mv $(SOFT_NAME) $(LIB_DIR)
	@mkdir -p $(ENV_DIR)
	@mkdir -p $(TEST_DIR)

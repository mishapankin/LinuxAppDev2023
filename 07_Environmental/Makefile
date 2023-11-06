BUILD_DIR=build
BIN_DIR=bin

.PHONY: all clean distclean

all:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	cd $(BUILD_DIR) && cmake .. && make

distclean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
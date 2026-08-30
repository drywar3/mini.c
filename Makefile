
INC_DIR = include
SRC_DIR = src
BUILD_DIR ?= build

SOURCES = $(shell find $(SRC_DIR) -type f -name *.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

TARGET_NAME ?= mini
TARGET = $(BUILD_DIR)/$(TARGET_NAME).a

COMPILER ?= gcc
OPTIONS  = -std=c17 -I$(INC_DIR)
CXX_OPTIONS ?=

OPTIONS += $(CXX_OPTIONS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(COMPILER) -o $@ -c $< $(OPTIONS)
	
tests: $(TARGET)
	@./run_tests.sh ./tests/ "$(TARGET)" "$(OPTIONS)"
.PHONY: tests

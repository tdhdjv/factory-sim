CC := g++
CONFIG ?= 
ASSEMBLY := longDayFactory
COMPILER_FLAGS := -g -O0 
INCLUDE_FLAGS := -Isrc/vendor -Isrc/
LINKER_FLAGS := -lm -lGL -lglut -lSDL3 -lglfw

BUILD_DIR := bin/$(CONFIG)
OBJ_DIR := obj/$(CONFIG)


SRC_FILES := $(shell find src -name "*.cpp")
DIRECTORIES := $(shell find src -type d)		# directories with .h files
OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)/%.o)		# compiled .o objects

all: scaffold compile link

.PHONY: scaffold
scaffold: # create build directory
	@echo Scaffolding folder structure...
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(DIRECTORIES))
	@echo Done.

.PHONY: link
link: scaffold $(OBJ_FILES) # link
	@echo Linking...
	@$(CC) $(OBJ_FILES) -o$(BUILD_DIR)/$(ASSEMBLY) $(LINKER_FLAGS)

.PHONY: compile
compile: #compile .c files
	@echo Compiling...
-include $(OBJ_FILES:.o=.d)
.PHONY: clean

clean: # clean build directory
	rm $(BUILD_DIR)/$(ASSEMBLY)
	rm -rf $(OBJ_DIR)

$(OBJ_DIR)/%.cpp.o: %.cpp # compile .c to .o object
	@echo   $<...
	@$(CC) $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS)
-include $(OBJ_FILES:.o=.d)


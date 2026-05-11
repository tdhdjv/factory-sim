CC := g++
CONFIG ?= debug
ASSEMBLY := longDayFactory
COMPILER_FLAGS := -g -O0 

BUILD_DIR := bin
OBJ_DIR := obj

PLATFORM ?= win32

ifeq ($(OS),Windows_NT)	
	PLATFORM := win32
	SRC_FILES := $(shell powershell -Command "Get-ChildItem -Recurse -Filter *.cpp src | Resolve-Path -Relative | ForEach-Object { $$_.TrimStart('.').TrimStart('\').Replace('\', '/') }")
	DIRECTORIES := $(shell powershell -Command "Get-ChildItem -Recurse -Directory src | Resolve-Path -Relative | ForEach-Object { $$_.Replace('\', '/') }")
	INCLUDE_FLAGS := -Isrc/vendor -Isrc/ -Iincludes
	LINKER_FLAGS := -Llib -lm -lopengl32 -lglfw3 -lgdi32 -ldwmapi
else
	PLATFORM := linux
	SRC_FILES := $(shell find src -name "*.cpp")
	DIRECTORIES := $(shell find src -type d)		# directories with .h files
	INCLUDE_FLAGS := -Isrc/vendor -Isrc
	LINKER_FLAGS := -lm -lGL -lglfw
endif

OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)/$(CONFIG)/%.o)		# compiled .o objects

all: scaffold compile link

scaffold: scaffold-$(PLATFORM)
.NOTPARALLEL: scaffold

.PHONY: scaffold-win32
scaffold-win32:
	@echo Scaffolding folder structure...
	-@powershell -Command "New-Item -ItemType Directory -Force '$(BUILD_DIR)/$(CONFIG)' | Out-Null"
	-@powershell -Command "New-Item -ItemType Directory -Force '$(OBJ_DIR)/$(CONFIG)/src' | Out-Null"
	-@powershell -Command "Get-ChildItem -Recurse -Directory src | ForEach-Object { New-Item -ItemType Directory -Force ('$(OBJ_DIR)/$(CONFIG)/' + $$_.FullName.Replace((Get-Location).Path + '\','').Replace('\','/')) | Out-Null }"
	@echo Done.

.PHONY: scaffold-linux
scaffold-linux: # create build directory
	@echo Scaffolding folder structure...
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(CONFIG)
	@mkdir -p $(addprefix $(OBJ_DIR)/$(CONFIG)/,$(DIRECTORIES))
	@echo Done.

.PHONY: link
link: link-$(PLATFORM)

.PHONY: link-win32
link-win32: scaffold $(OBJ_FILES)
	@echo Linking...
	-@copy lib\glfw3.dll $(BUILD_DIR)\$(CONFIG)\ >nul
	$(CC) $(OBJ_FILES) -o$(BUILD_DIR)/$(CONFIG)/$(ASSEMBLY) $(LINKER_FLAGS)

.PHONY: link-linux
link-linux: scaffold $(OBJ_FILES)
	@echo Linking...
	$(CC) $(OBJ_FILES) -o$(BUILD_DIR)/$(CONFIG)/$(ASSEMBLY) $(LINKER_FLAGS)

.PHONY: compile
compile: #compile .c files
	@echo Compiling...
-include $(OBJ_FILES:.o=.d)

.PHONY: clean

clean: clean-$(PLATFORM)
.NOTPARALLEL: clean

.PHONY: clean-linux
clean-linux: # clean build directory
	rm $(BUILD_DIR)/$(CONFIG)/$(ASSEMBLY)
	rm -rf $(OBJ_DIR)/$(CONFIG)

.PHONY: clean-win32
clean-win32: # clean build directory
	if exist $(BUILD_DIR)\$(ASSEMBLY)$(EXTENSION) del $(BUILD_DIR)\$(ASSEMBLY)$(EXTENSION)
	rmdir /s /q $(OBJ_DIR)\$(ASSEMBLY)

$(OBJ_DIR)/$(CONFIG)/%.cpp.o: %.cpp # compile .c to .o object
	@echo   $<...
	@$(CC) $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS)
-include $(OBJ_FILES:.o=.d)

FLAGS = -pedantic

SDL_DIR=dep/SDL2/MAC
DEP=-lSDL2-2.0.0

INCLUDE_PATH = $(SDL_DIR)/linclude
LIB_PATH = $(SDL_DIR)/lib

INC = -I$(INCLUDE_PATH)
LIB = -L$(LIB_PATH)

BUILD_PATH = Build

CXX := g++

OBJECT_FILES = $(BUILD_PATH)/Main.o \
			   $(BUILD_PATH)/Tween.o

PROGRAM_FILE = program


all: build

$(BUILD_PATH)/%.o: Library/%.cpp
	$(CXX) $(INC) -c $< -o $@

$(BUILD_PATH)/Main.o: Main.cpp
	$(CXX) $(INC) -c $< -o $@

build: $(OBJECT_FILES)
	@echo "** Building Game **"
	$(CXX) $(INC) $(LIB) $(FLAGS) -o $(PROGRAM_FILE) $(OBJECT_FILES)  $(DEP)

run: all
	./$(PROGRAM_FILE)

clean:
	@echo "** Removing object files and executable **"
	$(RM) $(BUILD_PATH)/*.o
	$(RM) $(PROGRAM_FILE)

install:
	@echo "** Installing **"
	cp $(PROGRAM_FILE) /usr/bin

uninstall:
	@echo "** Uninstalling **"
	$(RM) -f /usr/bin/$(PROGRAM_FILE)

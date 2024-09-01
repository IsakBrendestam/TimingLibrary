FLAGS = -pedantic
LIBS = 

INCLUDE_PATH = 
LIB_PATH = 

BUILD_PATH = Build

CXX := g++

OBJECT_FILES = $(BUILD_PATH)/Main.o \

PROGRAM_FILE = program


all: build

$(BUILD_PATH)/%.o: Library/%.cpp
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

$(BUILD_PATH)/Main.o: Main.cpp
	$(CXX) $(INCLUDE_PATH) -c $< -o $@

build: $(OBJECT_FILES)
	@echo "** Building Game **"
	$(CXX) $(INCLUDE_PATH) $(FLAGS) -o $(PROGRAM_FILE) $(OBJECT_FILES) $(LIB_PATH) $(LIBS)

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

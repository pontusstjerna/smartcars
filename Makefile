SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
ASSETS_DIR=assets
SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

ifeq ($(OS), Windows_NT)
	I_DIR=D:\\dev\\vcpkg\\installed\\x64-mingw-dynamic\\include
	L_DIR=D:\\dev\\vcpkg\\installed\\x64-mingw-dynamic\\lib -LD:\\dev\\vcpkg\\installed\\x64-mingw32-dynamic\\lib\\manual-link
else
	I_DIR=/mnt/d/dev/vcpkg/installed/x64-linux/include
	L_DIR=/mnt/d/dev/vcpkg/installed/x64-linux/lib
endif

ifeq ($(OS), Windows_NT)
	PLATFORM_LDFLAGS := -lmingw32
else
	SYS_FLAGS=-pthread
endif

CC=g++

LDFLAGS=-L$(L_DIR) $(PLATFORM_LDFLAGS) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lbox2d 
IFLAGS=-I$(I_DIR)
CPPFLAGS=-std=c++17 

all: print directories game

print:
	@echo Building...

directories: $(OBJ_DIR) $(BIN_DIR) $(BIN_DIR)/$(ASSETS_DIR)

$(OBJ_DIR): 
	mkdir $(OBJ_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BIN_DIR)/$(ASSETS_DIR):
ifeq ($(OS), Windows_NT)
	Xcopy /E /I $(ASSETS_DIR) $(BIN_DIR)\\$(ASSETS_DIR)\\
else
	cp -R $(ASSETS_DIR) $(BIN_DIR)/$(ASSETS_DIR)
endif

game: $(OBJ_FILES)
	@echo Linking...
	$(CC) $(CPPFLAGS) $(SYS_FLAGS) -g $^ $(LDFLAGS) -o $(BIN_DIR)/game

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.cpp
	$(CC) -c $(CPPFLAGS) -o $@ -g $< $(IFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) -o $@ -g $< $(IFLAGS)

.PHONY: clean directories

clean:
ifeq ($(OS), Windows_NT)
	rd /s /q $(OBJ_DIR) $(BIN_DIR)\\$(ASSETS_DIR)
	del /F $(BIN_DIR)\\game.exe
else
	rm -rf $(OBJ_DIR) $(BIN_DIR)/game
endif
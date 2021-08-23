SRC_DIR=src
OBJ_DIR=obj
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
	
else
	SYS_FLAGS=-pthread
endif

CC=g++

LDFLAGS=-L$(L_DIR) -lSDL2 -lSDL2_image -lSDL2main -lbox2d 
CPPFLAGS=-std=c++17 -I$(I_DIR)

all: print directories game

print:
	@echo Building...

directories: $(OBJ_DIR)

$(OBJ_DIR): 
	mkdir $(OBJ_DIR)

game: $(OBJ_FILES)
	@echo Linking...
	$(CC) $(SYS_FLAGS) -g $^ $(LDFLAGS) -o game

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.cpp
	$(CC) -c -o $@ -g $< $(CPPFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ -g $< $(CPPFLAGS)

.PHONY: clean directories

clean:
ifeq ($(OS), Windows_NT)
	rd /s /q obj
else
	rm -rf $(OBJ_DIR) game
endif
CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"/opt/homebrew/include/"
SRC_FILES = ./src/*.cpp \
			./src/**/*.cpp
LINKER_FLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf
OBJ_NAME = pong

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)


# Compiler
CC = g++
# Directories
INCLUDE_DIR = ./include
SRC_DIR = src
OBJ_DIR = obj


# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Targets
all: main

main: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

clean:
	rm -f main $(OBJ_DIR)/*.o


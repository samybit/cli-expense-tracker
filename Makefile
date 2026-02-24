# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -I./src

# Files to compile
SRC = src/main.c src/transaction.c src/storage.c src/utils.c
OBJ = $(SRC:.c=.o)

# Name of the final executable
EXEC = expense_tracker

# Default target
all: $(EXEC)

# Link the object files into the final executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compile each .c file into a .o (object) file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f src/*.o $(EXEC)
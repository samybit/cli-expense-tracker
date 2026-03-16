# Settings
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = expense_tracker

# Source and Object files
SRCS = src/main.c src/transaction.c src/utils.c src/storage.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET) data_dir

# Link the objects to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile C files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the data directory exists for the save file
data_dir:
	mkdir -p data

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
CC = gcc
CFLAGS = -Wall -Wextra -I./src
SRC = src/main.c src/transaction.c src/utils.c src/storage.c
OBJ = $(SRC:.c=.o)
EXEC = expense_tracker

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(EXEC)
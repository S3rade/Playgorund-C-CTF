CC = gcc
CFLAGS = -Wall -g -Iinclude   # Include the directory for headers
SOURCES = src/main.c src/game.c
OBJECTS = $(SOURCES:.c=.o)
EXEC = build/game

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(EXEC)
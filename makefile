CC = gcc
CFLAGS = -Wall -g -Iinclude
SOURCES = src/main.c src/game.c src/server.c
OBJECTS = $(SOURCES:.c=.o)
EXEC = build/game.exe

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS) -lWs2_32  

clean:
	del $(OBJECTS) $(EXEC)

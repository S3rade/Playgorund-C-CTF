CC = gcc
CFLAGS = -Wall -g -Iinclude
SOURCES = src/main.c src/game.c src/server.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = build/game.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

clean:
    del $(OBJECTS) $(TARGET)

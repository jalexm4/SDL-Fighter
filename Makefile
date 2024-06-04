CC = gcc
CFLAGS = -std=c18 -O3 -I include/ -Wall -Wextra
LDFLAGS = -L lib/ -lSDL2 -lSDL2_image -lSDL2_mixer -Wl,-rpath,lib/

TARGET = bin/game

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=bin/%.o)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

.PHONY: clean
clean:
	rm bin/*.o $(TARGET)

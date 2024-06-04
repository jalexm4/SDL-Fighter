CC = gcc
CFLAGS = -std=c18 -O3 -I include/ -Wall -Wextra
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_mixer

TARGET = bin/opengl

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=bin/%.o)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	bin/opengl

.PHONY: clean
clean:
	rm bin/*.o $(TARGET)

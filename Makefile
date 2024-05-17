cc = gcc
cflags = -std=c18 -Wall -Wextra -Wpedantic
lflags = `sdl2-config --cflags --libs`

build: main.c
	$(cc) -o bin/game main.c $(cflags) $(lflags)

run: build
	bin/game

clean:
	rm bin/game

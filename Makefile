cc = gcc
cflags = -std=c18 -Wall -Wextra -Wpedantic
lflags = `sdl2-config --cflags --libs` -lSDL2_image

build: src/main.c
	$(cc) -o bin/game src/main.c src/bullets.c src/collision.c src/enemies.c src/init.c src/input.c src/player.c $(cflags) $(lflags)

run: build
	bin/game

clean:
	rm bin/game

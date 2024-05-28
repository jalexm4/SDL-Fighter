cc = gcc
cflags = -std=c18 -Wall -Wextra -Wpedantic
lflags = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_mixer

build: src/main.c
	$(cc) -o bin/game src/main.c src/audio.c src/background.c src/bullets.c src/collision.c src/enemies.c src/hud.c src/init.c src/input.c src/player.c src/vfx.c $(cflags) $(lflags)

run: build
	bin/game

clean:
	rm bin/game

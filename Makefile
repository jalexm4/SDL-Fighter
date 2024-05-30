CC = gcc
CFLAGS = -std=c18 -O3 -Wall -Wextra -Wpedantic
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_mixer

TARGET = bin/game

$(TARGET): src/main.c
	$(CC) -o $@ src/main.c src/audio.c src/background.c src/bullets.c src/collision.c src/enemies.c src/hud.c src/init.c src/input.c src/player.c src/vfx.c $(CFLAGS) $(LDFLAGS)

run: $(TARGET)
	bin/game

clean:
	rm bin/game

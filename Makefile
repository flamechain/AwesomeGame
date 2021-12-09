VERSION=debug

SOURCE_FILES:=$(wildcard src/*.cpp)
OBJECT_FILES:=$(patsubst src/%.cpp, bin/temp/%.o, $(SOURCE_FILES))

OUTFILE:="bin/$(VERSION)/game.exe"

CC=g++
CCFLAGS=-Iinclude -Ilib/SDL
LDFLAGS=-Llib/SDL/lib -Llib/SDL_IMAGE/lib -lSDL2 -lSDL2_image

all: $(SOURCE_FILES) link

.PHONY: $(SOURCE_FILES)

$(SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/%.cpp, bin/temp/%.o, $@)

link:
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o $(OUTFILE)

dirs:
	mkdir -p bin
	mkdir -p bin/temp
	mkdir -p bin/debug
	mkdir -p bin/release

clean:
	rm -f bin/**/*.o

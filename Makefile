VERSION=debug

SOURCE_FILES:=$(wildcard src/*.cpp)
OBJECT_FILES:=$(patsubst src/%.cpp, bin/temp/%.o, $(SOURCE_FILES))

OUTFILE:="bin/$(VERSION)/game.exe"

CC=g++
CCFLAGS=-Iinclude -Ilib/SDL
CCFLAGS+=-Dmain=SDL_main
LDFLAGS=-L"./lib/SDL/lib" -lSDL2_image -Wl,-Bdynamic
# -mwindows
LDFLAGS+=-lmingw32 -lSDL2main -lSDL2 -Wl,--dynamicbase \
-Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 \
-luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 \
-lsetupapi -lversion -luuid

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

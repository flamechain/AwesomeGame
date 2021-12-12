VERSION=debug

SOURCE_FILES:=$(wildcard src/*.cpp)
OBJECT_FILES:=$(patsubst src/%.cpp, bin/temp/%.o, $(SOURCE_FILES))

OUTFILE:="bin/$(VERSION)/game.exe"

CC=g++
CCFLAGS=-Iinclude -Ilib/SDL -Wall -Wextra# general
CCFLAGS+=-Dmain=SDL_main # sdl specific
LDFLAGS=-L./lib/SDL/lib -lSDL2_image -Wl,-Bdynamic -Wall -Wextra# general
# LDFLAGS+=-mwindows
LDFLAGS+=-lmingw32 -lSDL2main -lSDL2 -Wl,--dynamicbase \
-Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 \
-luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 \
-lsetupapi -lversion -luuid -lz # sdl specific

all: $(SOURCE_FILES) link

setup: dirs dlibs rlibs

.PHONY: $(SOURCE_FILES)

$(SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/%.cpp, bin/temp/%.o, $@)

link:
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o $(OUTFILE)

dirs:
	mkdir -p bin/temp
	mkdir -p bin/debug
	mkdir -p bin/release

libs:
	cp -u bin/lib/libjpeg-9.dll bin/debug
	cp -u bin/lib/libpng16-16.dll bin/debug
	cp -u bin/lib/libtiff-5.dll bin/debug
	cp -u bin/lib/libwebp-4.dll bin/debug
	cp -u bin/lib/libjpeg-9.dll bin/release
	cp -u bin/lib/libpng16-16.dll bin/release
	cp -u bin/lib/libtiff-5.dll bin/release
	cp -u bin/lib/libwebp-4.dll bin/release

clean:
	rm -f bin/**/*.o

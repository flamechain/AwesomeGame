VERSION=debug

SOURCE_FILES:=$(wildcard src/*.cpp)
OBJECT_FILES:=$(patsubst src/%.cpp, bin/temp/%.o, $(SOURCE_FILES))

OUTFILE:="bin/$(VERSION)/game.exe"

CC=g++
CCFLAGS=-Iinclude -Ilib/SDL -Wall -Wextra # general
CCFLAGS+=-Dmain=SDL_main # sdl specific
CCFLAGS+=-Llib/SDL/lib
LDFLAGS=-Llib/SDL/lib -Lbin/release -lSDL2_image -lSDL2_ttf -llibfreetype-6 -Wl,-Bdynamic -Wall -Wextra # general
# LDFLAGS+=-mwindows
LDFLAGS+=-lmingw32 -lSDL2main -lSDL2 -Wl,--dynamicbase \
-Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 \
-luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 \
-lsetupapi -lversion -luuid -lz # sdl specific

all: $(SOURCE_FILES) link
setup: dirs libs

.PHONY: $(SOURCE_FILES)

$(SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/%.cpp, bin/temp/%.o, $@)

link:
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o $(OUTFILE)

dirs:
	mkdir -p bin/temp
	mkdir -p bin/debug

libs:
	cp -u bin/release/libjpeg-9.dll bin/debug
	cp -u bin/release/libpng16-16.dll bin/debug
	cp -u bin/release/libtiff-5.dll bin/debug
	cp -u bin/release/libwebp-4.dll bin/debug
	cp -u bin/release/libfreetype-6.dll bin/debug

clean:
	rm -f bin/**/*.o

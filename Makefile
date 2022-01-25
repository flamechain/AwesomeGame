VERSION=debug

SOURCE_FILES=$(wildcard src/*.cpp)
OBJECT_FILES=$(patsubst src/%.cpp, bin/MinGW/temp/%.o, $(SOURCE_FILES))

OUTFILE="bin/MinGW/$(VERSION)/dissension.exe"

CC=g++
INNO=iscc
INSTALL=$(wildcard src/*.iss)
CCFLAGS=-Iinclude -Ilib/SDL # general
# CCFLAGS+=-Wall -Wextra
CCFLAGS+=-Llib/MinGW -Dmain=SDL_main # sdl specific
LDFLAGS=-Llib/MinGW -Lbin/MinGW/release -lSDL2_image -lSDL2_ttf -llibfreetype-6 -Wl,-Bdynamic -Wall -Wextra # general
# LDFLAGS+=-mwindows
LDFLAGS+=-lmingw32 -lSDL2main -lSDL2 -Wl,--dynamicbase \
-Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 \
-luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 \
-lsetupapi -lversion -luuid -lz # sdl specific

all: $(SOURCE_FILES) link
setup: dirs libs

.PHONY: $(SOURCE_FILES)

$(SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/%.cpp, bin/MinGW/temp/%.o, $@)

installer:
	$(INNO) $(INSTALL)

link:
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o $(OUTFILE)

dirs:
	mkdir -p bin/MinGW/temp
	mkdir -p bin/MinGW/debug
	mkdir -p bin/MinGW/debug/saves
	mkdir -p bin/MinGW/release/saves

libs:
	cp -u lib/share/libjpeg-9.dll bin/MinGW/debug
	cp -u lib/share/libpng16-16.dll bin/MinGW/debug
	cp -u lib/share/libtiff-5.dll bin/MinGW/debug
	cp -u lib/share/libwebp-4.dll bin/MinGW/debug
	cp -u lib/share/libfreetype-6.dll bin/MinGW/debug
	cp -u lib/share/libjpeg-9.dll bin/MinGW/release
	cp -u lib/share/libpng16-16.dll bin/MinGW/release
	cp -u lib/share/libtiff-5.dll bin/MinGW/release
	cp -u lib/share/libwebp-4.dll bin/MinGW/release
	cp -u lib/share/libfreetype-6.dll bin/MinGW/release

clean:
	rm -f bin/MinGW/**/*.o

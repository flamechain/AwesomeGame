VERSION=debug

SOURCE_FILES=$(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
OBJECT_FILES=$(patsubst src/%.cpp, bin/MinGW/temp/%.o, $(SOURCE_FILES))

OUTFILE="bin/MinGW/$(VERSION)/dissension.exe"

CC=g++
INNO=iscc

CCFLAGS=-Iinclude -Iinclude/engine -Iinclude/game -Ilib/SDL
CCFLAGS+=-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy \
-Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations \
-Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual \
-Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
-Wundef -Wno-unused -Werror
# CCFLAGS+=-Wredundant-decls -Wswitch-default # sdl headers trigger these
CCFLAGS+=-Llib/MinGW -Dmain=SDL_main # sdl specific
LDFLAGS=-Llib/MinGW -Lbin/MinGW/release -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llibfreetype-6 -Wl,-Bdynamic
# LDFLAGS+=-mwindows
LDFLAGS+=-lmingw32 -lSDL2main -lSDL2 -Wl,--dynamicbase \
-Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 \
-luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 \
-lsetupapi -lversion -luuid -lz # sdl specific

all: $(OUTFILE)
setup: dirs libs

bin/MinGW/temp/%.o: src/%.cpp
	$(CC) $(CCFLAGS) -c $^ -o $@

installer:
	$(INNO) src/mingw.iss

$(OUTFILE): $(OBJECT_FILES)
	$(CC) $^ $(LDFLAGS) -o $(OUTFILE)

dirs:
	mkdir -p bin/MinGW/temp
	mkdir -p bin/MinGW/temp/engine
	mkdir -p bin/MinGW/temp/game
	mkdir -p bin/MinGW/debug
	mkdir -p bin/MinGW/debug/saves
	mkdir -p bin/MinGW/release/saves

libs:
	cp -u -a lib/share/. bin/MinGW/debug
	cp -u -a lib/share/. bin/MinGW/release

clean:
	rm -f bin/MinGW/temp/**/*.o
	rm -f bin/MinGW/temp/*.o

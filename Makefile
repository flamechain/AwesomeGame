VERSION=debug

SOURCE_FILES=$(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
OBJECT_FILES=$(patsubst src/%.cpp, bin/temp/%.o, $(SOURCE_FILES))

OUTFILE="bin/$(VERSION)/dissension.exe"

CC=g++
INNO=iscc

CCFLAGS=-Iinclude -Iinclude/engine -Iinclude/game -Ilib/SDL
CCFLAGS+=-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy \
-Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations \
-Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual \
-Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
-Wundef -Wno-unused -Werror
# CCFLAGS+=-Wredundant-decls -Wswitch-default # sdl headers trigger these
CCFLAGS+=-Llib/static -Dmain=SDL_main # sdl specific
LDFLAGS=-Llib/static -Lbin/release -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llibfreetype-6 -Wl,-Bdynamic
# LDFLAGS+=-mwindows
DLFLAGS=-lSDL2_dll -lSDL2_image_dll -lSDL2_ttf_dll -lSDL2_mixer_dll
STFLAGS=-lmingw32 -lSDL2main -lSDL2 -Wl,--dynamicbase \
-Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 \
-luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 \
-lsetupapi -lversion -luuid -lz # sdl specific

all: $(OUTFILE)
dyn: 
setup: dirs libs

bin/temp/%.o: src/%.cpp
	$(CC) $(CCFLAGS) -c $^ -o $@

installer:
	$(INNO) src/install.iss

$(OUTFILE): $(OBJECT_FILES)
	$(CC) $^ $(LDFLAGS) $(STFLAGS) -o $(OUTFILE)

dyn: $(OBJECT_FILES)
	$(CC) $^ $(LDFLAGS) $(DLFLAGS) -o $(OUTFILE)

dirs:
	mkdir -p bin/temp
	mkdir -p bin/temp/engine
	mkdir -p bin/temp/game
	mkdir -p bin/debug
	mkdir -p bin/debug/saves
	mkdir -p bin/release/saves

libs:
	cp -u -a lib/share/. bin/debug
	cp -u -a lib/share/. bin/release
# cp -u -a lib/dll/. bin/debug
# cp -u -a lib/dll/. bin/release

clean:
	rm -f bin/temp/**/*.o
	rm -f bin/temp/*.o

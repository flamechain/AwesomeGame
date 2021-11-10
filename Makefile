VERSION=debug

MAIN_SOURCE_FILES:=$(wildcard src/*.cpp)
C_SOURCE_FILES:=$(wildcard src/**/*.c)
GAME_SOURCE_FILES:=$(wildcard src/game/*.cpp)
ENGINE_SOURCE_FILES:=$(wildcard src/engine/**/*.cpp)

# update to do rendering seperate
MAIN_OBJECT_FILES:=$(patsubst src/%.cpp, bin/temp/%.o, $(MAIN_SOURCE_FILES))
C_OBJECT_FILES:=$(patsubst src/**/%.c, bin/temp/%.o, $(C_SOURCE_FILES))
GAME_OBJECT_FILES:=$(patsubst src/game/%.cpp, bin/temp/%.o, $(GAME_SOURCE_FILES))
ENGINE_OBJECT_FILES:=$(patsubst src/engine/**/%.cpp, bin/temp/%.o, $(ENGINE_SOURCE_FILES))

OBJECT_FILES:=$(MAIN_OBJECT_FILES) $(GAME_OBJECT_FILES) $(ENGINE_OBJECT_FILES) $(C_OBJECT_FILES)
OUTFILE:="bin/$(VERSION)/game.exe"

CC=g++
CCFLAGS=-Ilib/glfw/include -Iinclude -Ilib/glew/include -Ilib/freeglut/include -Ilib/glm/include
CCFLAGS+=-Ilib/glad/include
LDFLAGS=-Llib/glew/lib -lglew32 -lglfw3 -lopengl32 -lgdi32
# LDFLAGS+=-Llib/freeglut/lib/x64 -lglu32 -lfreeglut -lm

all: $(MAIN_SOURCE_FILES) $(C_SOURCE_FILES) $(GAME_SOURCE_FILES) $(ENGINE_SOURCE_FILES) link

.PHONY: $(MAIN_SOURCE_FILES)
.PHONY: $(GAME_SOURCE_FILES)
.PHONY: $(ENGINE_SOURCE_FILES)
.PHONY: $(C_SOURCE_FILES)

$(MAIN_SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/%.cpp, bin/temp/%.o, $@)

$(C_SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/engine/%.c, bin/temp/%.o, $@)

$(GAME_SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/game/%.cpp, bin/temp/%.o, $@)

$(ENGINE_SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/engine/**/%.cpp, bin/temp/%.o, $@)

link:
# $(CC) $(OBJECT_FILES) $(LDFLAGS) -o game.exe
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o $(OUTFILE)

dirs:
	mkdir -p bin
	mkdir -p bin/temp
	mkdir -p bin/debug
	mkdir -p bin/release

clean:
	rm -f bin/*.o

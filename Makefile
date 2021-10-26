MAIN_SOURCE_FILES:=$(wildcard src/*.cpp)
GAME_SOURCE_FILES:=$(wildcard src/game/*.cpp)
RENDERING_SOURCE_FILES:=$(wildcard src/rendering/*.cpp)

OBJECT_FILES=
MAIN_OBJECT_FILES:=$(patsubst src/%.cpp, bin/%.o, $(MAIN_SOURCE_FILES))
GAME_OBJECT_FILES:=$(patsubst src/game/%.cpp, bin/%.o, $(GAME_SOURCE_FILES))
RENDERING_OBJECT_FILES:=$(patsubst src/rendering/%.cpp, bin/%.o, $(RENDERING_SOURCE_FILES))

OBJECT_FILES+=$(MAIN_OBJECT_FILES)
OBJECT_FILES+=$(GAME_OBJECT_FILES)
OBJECT_FILES+=$(RENDERING_OBJECT_FILES)

CC=g++
CCFLAGS=-Ilib/glfw/include -Iinclude -Ilib/glew/include -Ilib/freeglut/include -Ilib/glm/include
LDFLAGS=-Llib/glew/lib -lglew32 -lglfw3 -lopengl32 -lgdi32
# LDFLAGS+=-Llib/freeglut/lib/x64 -lglu32 -lfreeglut -lm

all: $(MAIN_SOURCE_FILES) $(GAME_SOURCE_FILES) $(RENDERING_SOURCE_FILES) link

.PHONY: $(MAIN_SOURCE_FILES)
.PHONY: $(GAME_SOURCE_FILES)
.PHONY: $(RENDERING_SOURCE_FILES)

$(MAIN_SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/%.cpp, bin/%.o, $@)

$(GAME_SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/game/%.cpp, bin/%.o, $@)

$(RENDERING_SOURCE_FILES):
	$(CC) $(CCFLAGS) -c $@ -o $(patsubst src/rendering/%.cpp, bin/%.o, $@)

link:
# $(CC) $(OBJECT_FILES) $(LDFLAGS) -o game.exe
	$(CC) bin/display.o bin/game.o bin/main.o $(LDFLAGS) -o game.exe

clean:
	rm -f bin/*.o

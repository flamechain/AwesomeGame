SOURCE_FILES=$(wildcard src/*.cpp)
SOURCE_FILES+=$(wildcard src/**/*.cpp)
SOURCE_FILES+=$(wildcard src/**/**/*.cpp)
OBJECT_FILES:=$(patsubst src/%.cpp, bin/%.o, $(SOURCE_FILES))

CC=g++
CCFLAGS= -Ilib/glfw/include -Iinclude -Ilib
# CCFLAGS+=-Ilib/glew/include -Ilib/freeglut/include -Ilib/glm/include
LDFLAGS= -lglfw3 -lopengl32 -lgdi32 -lm
# LDFLAGS+=-Llib/freeglut/lib/x64 -Llib/glew/lib
# LDFLAGS+=-lglu32 -lgdi32 -lopengl32 -lfreeglut -lglew32

all: cc

cc:
	$(CC) $(CCFLAGS) $(SOURCE_FILES) $(LDFLAGS) -o game.exe

clean:
	rm -f bin/*.o

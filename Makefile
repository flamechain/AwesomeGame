SOURCE_FILES:=$(wildcard src/*.cpp)
OBJECT_FILES:=$(patsubst src/%.cpp, bin/%.o, $(SOURCE_FILES))

CC=g++
CCFLAGS=-Ilib/glfw/include -Ilib/glew/include -Ilib/freeglut/include
LDFLAGS=-Llib/glfw/lib-mingw-w64 -Llib/freeglut/lib/x64 -Llib/glew/lib -lopengl32 -lglfw3 -lfreeglut -lglew32
LDFLAGS+=-lglu32 -lgdi32

all: $(SOURCE_FILES) link

.PHONY:$(SOURCE_FILES)
$(SOURCE_FILES):
	$(CC) -c $(CCFLAGS) $@ -o $(patsubst src/%.cpp, bin/%.o, $@)

link:
	$(CC) $(OBJECT_FILES) $(LDFLAGS) -o game.exe

clean:
	rm -f bin/*.o

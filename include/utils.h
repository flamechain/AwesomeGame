#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>

#include <cerrno>
#include <cstdio>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using std::printf;
using std::vector;
using std::string;
using namespace std::this_thread;
using namespace std::chrono;

/// Sends text output to stdout
/// @param Format   format string (same syntax as printf)
inline void ConsoleOutput(const char * Format, ...) {
    va_list argptr;
    va_start(argptr, Format);
    vfprintf(stderr, Format, argptr);
    va_end(argptr);
}

// SDL_Color without alpha channel
struct Color {
    int r;
    int g;
    int b;
};

#endif

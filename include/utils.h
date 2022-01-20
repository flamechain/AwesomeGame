#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>

#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>
#include <map>
#include <stdexcept>

#include <math.h>

using std::printf;
using std::vector;
using std::string;
using std::map;
using namespace std::this_thread;
using namespace std::chrono;

class Screen;
typedef void (*callback)(void);
typedef void (*screen_callback)(Screen*, string uid);

/// Sends text output to stdout
/// @param Format   format string (same syntax as printf)
inline void ConsoleOutput(const char * Format, ...) {
    va_list argptr;
    va_start(argptr, Format);
    vfprintf(stderr, Format, argptr);
    va_end(argptr);
}

inline string StringFormat(const std::string& Format, ...) {
    va_list argptr;
    va_start(argptr, Format);
    const int size_s = std::vsnprintf(nullptr, 0, Format.c_str(), argptr) + 1; // +1 for terminator
    va_end(argptr);
    va_start(argptr, Format); // reset argptr, probaly better way to do this
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::vsnprintf(buf.get(), size, Format.c_str(), argptr);
    va_end(argptr);
    return string(buf.get(), buf.get() + size - 1); // remove terminator space
}

// SDL_Color without alpha channel
struct Color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
};

inline Color RGB(Uint8 r, Uint8 g, Uint8 b) {
    Color rgb;
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    return rgb;
}

#endif

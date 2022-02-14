#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <malloc.h>

#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <thread>
#include <memory>
#include <map>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "config.h"

using std::printf;
using std::vector;
using std::string;
using std::map;
using namespace std::this_thread;
using namespace std::chrono;

class Screen;
typedef void (*callback)(void);
typedef void (*screen_callback)(Screen&, string uid);

/// Sends text output to stdout
/// @param format   format string (same syntax as printf)
void ConsoleOutput(const char *format, ...);

/// Sends text output to stdout if debug
/// @param debug    if program is running in debug mode
/// @param format   format string
void DebugOutput(bool debug, const char *format, ...);

/// Formats a string; safer than sprintf
/// @param format   format string
/// @return formatted string
string StringFormat(const std::string& format, ...);

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

inline bool FileExists(const string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

#define WHITE RGB(255, 255, 255)
#define BLACK RGB(0, 0, 0)
#define GREY RGB(170, 170, 170)
#define LIGHT_GREY RGB(200, 200, 200)
#define DARK_GREY RGB(100, 100, 100)
#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)

#endif

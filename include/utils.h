#ifndef UTILS_H
#define UTILS_H

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdio.h>
#include <string>
#include <errno.h>

inline void ConsoleOutput(const char * Format, ...) {
    va_list argptr;
    va_start(argptr, Format);
    vfprintf(stderr, Format, argptr);
    va_end(argptr);
}

#endif

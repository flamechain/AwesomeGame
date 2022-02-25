#include "utils.h"

GAME_START

string StringFormat(const string& format, ...) {
    va_list argptr;
    va_start(argptr, format);
    const int size_s = std::vsnprintf(nullptr, 0, format.c_str(), argptr) + 1; // +1 for terminator
    va_end(argptr);
    va_start(argptr, format); // reset argptr, probaly better way to do this
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::vsnprintf(buf.get(), size, format.c_str(), argptr);
    va_end(argptr);
    return string(buf.get(), buf.get() + size - 1); // remove terminator space
}

void ConsoleOutput(const char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, format, argptr);
    va_end(argptr);
}

void DebugOutput(const char *format, ...) {
    if (!debug_mode) return;

    va_list argptr;
    va_start(argptr, format);
    string format_s = string("Debug: ") + format;
    vfprintf(stderr, format_s.c_str(), argptr);
    va_end(argptr);
}

GAME_END

#include "utils.h"

string StringFormat(const std::string& format, ...) {
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

#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <assert.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <unistd.h>

#include "GLM/vec2.hpp"

using Vector2 = glm::vec2;
using string = std::string;

template<class _Ty>
    using vector = std::vector<_Ty>;

#endif

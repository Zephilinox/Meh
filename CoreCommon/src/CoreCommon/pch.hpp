#pragma once

// CMake bug https://gitlab.kitware.com/cmake/cmake/-/issues/21219
// MSVC will emit warnings for the PCH, so force warning level to 1 to help hide them
#if defined(_MSC_VER)
    #define _WIN32_WINNT 0x0601
    #pragma warning(push, 1)
    #pragma warning(disable : 4619)
#endif

//Std Library stuff
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <memory>
#include <functional>
#include <array>
#include <mutex>
#include <atomic>
#include <thread>
#include <type_traits>
#include <cstdint>

#include <glm/glm.hpp>

//Asio things
#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#if defined(_MSC_VER)
    #pragma warning(pop)
#endif
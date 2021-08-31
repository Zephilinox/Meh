#pragma once

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
#if defined(_MSC_VER)
    #define _WIN32_WINNT=0x0601
    #pragma warning(push)
    #pragma warning(disable : 4619)
#endif
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif
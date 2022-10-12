#pragma once

#include <algorithm>
#include <array>
#include <assert.h>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <memory>
#include <mutex>
#include <numbers>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// Set value to 1 to use the Profiling system
#define PROFILING 1

#include "Profiling/Instrumentor.hpp"
#include "Profiling/Timer.hpp"

// define DEBUG macros here
#ifdef DEBUG

#endif

inline const int kCORE_COUNT = static_cast<int>(std::thread::hardware_concurrency());

#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <direct.h>
#include <windows.h>

// inline const std::string BINARY_DIRECTORY(std::string(_getcwd(NULL, 0)) + '/');
inline const std::string BINARY_DIRECTORY = std::filesystem::current_path().string();

#else

#include <unistd.h>

// inline const std::string BINARY_DIRECTORY_TEST(std::string(get_current_dir_name()) + "/");
inline const std::string BINARY_DIRECTORY = std::filesystem::current_path().string();

#endif

#define kEpsilon 0.000001

/**
 * @brief Prints the variables given to the console
 *
 * @tparam First stringstream-able type
 * @tparam Strings restof the stringstream-able types
 * @param arg
 * @param rest
 */
template <typename First, typename... Strings>
void print_by_force(First arg, [[maybe_unused]] const Strings &...rest)
{
    std::cout << arg;
    if constexpr (sizeof...(rest) > 0) [[likely]]
    {
        print_by_force(rest...);
    }
}

/**
 * @brief Prints the variables given to the console in an async manner
 *
 * @tparam First stringstream-able type
 * @tparam Strings restof the stringstream-able types
 * @param arg
 * @param rest
 */
template <typename First, typename... Strings>
void async_print_by_force(const First arg, const Strings &...rest)
{
    std::thread t([&]()
                  { print_by_force(arg, rest...); });
    t.detach();
}

#ifdef DEBUG

#define debug_print(x, y) print_by_force(x, y)
#define debug_async_print(x, y) async_print_by_force(x, y)
#else
#define debug_print(x, y)
#define debug_async_print(x, y)

#endif

/**
 * @brief Checks if the given class is of type Base
 *
 * @tparam Base base class
 * @tparam T subclass to check
 * @param T
 */
template <typename Base, typename T>
inline constexpr int instanceof (const T *)
{
    return std::is_base_of<Base, T>::value;
}

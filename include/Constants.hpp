#pragma once

#include <algorithm>
#include <array>
#include <assert.h>
#include <chrono>
#include <cstdio>
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
 * @brief A random number generator
 *
 * @tparam T The type of the random number
 *
 * @param min The minimum value of the random number
 * @param max The maximum value of the random number
 */
template <typename T>
[[nodiscard]] inline auto random(T min = 0.0, T max = 1.0) -> T
{
    thread_local std::random_device rd;
    thread_local std::mt19937 gen(rd());
    thread_local std::uniform_real_distribution<> dis(min, max);
    return static_cast<T>(dis(gen));
}

/**
 * @brief Map a value from one range to another
 *
 * @tparam T The type of the value
 * @param value The value to map
 * @param min The minimum value of the range
 * @param max The maximum value of the range
 * @param new_min The minimum value of the new range
 * @param new_max The maximum value of the new range
 * @return constexpr T
 */
template <typename T>
[[nodiscard]] inline auto constexpr map_to_range(T value, T min, T max, T new_min, T new_max) -> T
{
    return static_cast<T>(((value - min) / (max - min)) * (new_max - new_min) + new_min);
}

/**
 * @brief Prints the variables given to the console
 *
 * @tparam First stringstream-able type
 * @tparam Strings restof the stringstream-able types
 * @param arg
 * @param rest
 */
template <typename First, typename... Strings>
inline auto print_by_force(First arg, [[maybe_unused]] const Strings &...rest_of_args) -> void
{

    std::ostringstream os;
    os << arg;
    ((os << rest_of_args), ...);

    std::puts(os.str().c_str());
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
inline auto async_print_by_force(const First arg, const Strings &...rest) -> void
{
    std::thread t([&]()
                  { print_by_force(arg, rest...); std::cout << std::endl; });
    t.detach();
}

#ifdef DEBUG

#define debug_print(x, ...) print_by_force(x, __VA_ARGS__);
#define debug_async_print(x, ...) async_print_by_force(x, __VA_ARGS__);

#else

#define debug_print(x, ...) ;
#define debug_async_print(x, ...) ;

#endif

/**
 * @brief Checks if the given class is of type Base
 *
 * @tparam Base base class
 * @tparam T subclass to check
 * @param T
 */
template <typename Base, typename T>
inline auto constexpr instanceof (const T *) -> int
{
    return std::is_base_of<Base, T>::value;
}

// Set value to 1 to use the Profiling system
#define PROFILING 1

#include "Profiling/Instrumentor.hpp"
#include "Profiling/Timer.hpp"
#pragma once

#include "json.hpp"
#include "stb_image_write.h"
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
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define PROFILING 0

#include "Profiling/Instrumentor.hpp"
#include "Profiling/Timer.hpp"

// DEBUG MACROS
#ifdef DEBUG

#endif

const int kCORE_COUNT = std::thread::hardware_concurrency();

#ifdef _WIN32

#define NOMINMAX
#include <direct.h>
#include <windows.h>

const std::string BINARY_DIRECTORY(std::string(_getcwd(NULL, 0)) + '/');
const std::string TEST_DIRECTORY = std::filesystem::current_path().string();

#else

#include <filesystem>
#include <unistd.h>

const std::string BINARY_DIRECTORY(std::string((char *)std::filesystem::current_path().c_str()) + "/");
const std::string BINARY_DIRECTORY_TEST(std::string(get_current_dir_name()) + "/");

#endif

#define kEpsilon 0.000001

void debug_print()
{
    std::cout << std::endl;
}

template <typename First, typename... Strings>
[[nodiscard]] void debug_print([[maybe_unused]] First arg, [[maybe_unused]] const Strings &...rest)
{

#ifdef DEBUG

    std::cout << arg << " ";
    debug_print(rest...);

#endif
}

template <typename Base, typename T>
inline constexpr int instanceof (const T *)
{
    return std::is_base_of<Base, T>::value;
}

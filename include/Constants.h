#pragma once

#include <algorithm>
#include <array>
#include <assert.h>
#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
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
#define TIMER_ENABLED 0

#include "Profiling/Instrumentor.h"
#include "Profiling/Timer.h"

// DEBUG MACROS
#ifdef DEBUG

#endif


#ifdef _WIN32

#include <direct.h>
#include <windows.h>

const std::string BINARY_DIRECTORY(std::string(_getcwd(NULL, 0)) + '/');

#else

#include <filesystem>
#include <unistd.h>

const std::string BINARY_DIRECTORY(std::string((char *)std::filesystem::current_path().c_str()) + "/");
const std::string BINARY_DIRECTORY_TEST(std::string(get_current_dir_name()) + "/");

#endif

#define _unlikely [[unlikely]]

#define _likely [[likely]]

#define _maybe_unused [[maybe_unused]]

#define _deprecated [[deprecated]]

#define _nodiscard [[nodiscard]]

#define _optimize_for_synchronized [[optimize_for_synchronized]]

#define kEpsilon 0.000001

void debug_print()
{
    std::cout << std::endl;
}

template <typename First, typename... Strings>
_maybe_unused void debug_print(_maybe_unused First arg, _maybe_unused const Strings &...rest)
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

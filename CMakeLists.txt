# Set CMake version number
cmake_minimum_required(VERSION 3.16)

# Change "Temp-Projekt" to your project name
project(Temp-Projekt VERSION 0.2.0 LANGUAGES CXX)
enable_language(CXX)

#----------------------------------------------------------------------------------------------
# Part till line 46 is taken from @lefticus

# set a default CXX standard used by the external tools like clang-tidy, cppcheck, etc.
# You can later set fine-grained standards for each target using `target_compile_features`
set(CMAKE_CXX_STANDARD 17)

### Add project_options
# include(FetchContent)
# FetchContent_Declare(_project_options URL https://github.com/cpp-best-practices/project_options/archive/refs/heads/main.zip)
# FetchContent_MakeAvailable(_project_options)
# include(${_project_options_SOURCE_DIR}/Index.cmake)
include(CMakeSetupFiles/Index.cmake)

# run_vcpkg()

# Initialize project_options
# uncomment the options to enable them
project_options(
#   ENABLE_CACHE
#   ENABLE_CONAN
  WARNINGS_AS_ERRORS
#   ENABLE_CPPCHECK
#   ENABLE_CLANG_TIDY
#   ENABLE_INCLUDE_WHAT_YOU_USE
#   ENABLE_COVERAGE
#   ENABLE_PCH
#   PCH_HEADERS <Eigen/Dense> <fmt/core.h> <vector> <utility> <string> <string_view>
#   ENABLE_DOXYGEN
#   ENABLE_IPO
#   ENABLE_USER_LINKER
#   ENABLE_BUILD_WITH_TIME_TRACE
#   ENABLE_UNITY
#   ENABLE_SANITIZER_ADDRESS
#   ENABLE_SANITIZER_LEAK
#   ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
#   ENABLE_SANITIZER_THREAD
#   ENABLE_SANITIZER_MEMORY
  CLANG_WARNINGS "-Weverything"
)

#----------------------------------------------------------------------------------------------

#----------------------------------------------------------------------------------------------
# Part till line 68 is very very similar to that of @codetechandtutorials

#           DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote --merge
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#----------------------------------------------------------------------------------------------

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Build not specified, defaulted to Debug" FORCE)
    message(STATUS "Build type not specified, defaulted to Debug")
endif(NOT CMAKE_BUILD_TYPE)

# Add locations of other CMakelists.txt (one per call)
add_subdirectory(
    src
)

# Comment these 2 out if you don't intend on using CTests
include(CTest)
enable_testing()

# Extra C++ specific option I need
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# <-- Set standard here -->
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
# <----------------------->

# <-- Define warnings to show -->
target_link_libraries(${PROJECT_NAME} PRIVATE project_options project_warnings)
# <----------------------->

# <-- Comment out if you don't need CPack -->
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
# <----------------------------------------->

# <-- Define Compile Time Definitions here: -->
target_compile_definitions(${PROJECT_NAME} PRIVATE
     $<$<CONFIG:Debug>:DEBUG=1>
     $<$<CONFIG:RelWithDebInfo>:DEBUG=1>
     $<$<CONFIG:Release>:NDEBUG=1>
     $<$<CONFIG:MinSizeRel>:NDEBUG=1>
)
# <------------------------------------------->

# <-- Add directories to include directory here: -->
target_include_directories(${PROJECT_NAME}
    PUBLIC src
    PUBLIC include
)
# <------------------------------------------------>

# <-- Add directory of external libs to link here: -->
target_link_directories(${PROJECT_NAME}
     PRIVATE src # this line is just to prevent errors
)
# <-------------------------------------------------->

# <-- Link needed Libs: -->
target_link_libraries(${PROJECT_NAME} 
    PRIVATE project_options project_warnings
)
# <----------------------->
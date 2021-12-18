# Set CMake version number
cmake_minimum_required(VERSION 3.13)

# Change "Temp-Projekt" to your project name
project(Temp-Projekt VERSION 0.1.0)

#----------------------------------------------------------------------------------------------
# Part till line 39 is taken from @lefticus

# Link this 'library' to use the standard warnings
add_library(project_warnings INTERFACE)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

if(MSVC)
     target_compile_options(project_warnings INTERFACE /W4 /WX "/permissive-")
else()
                    # <-- Set standard here -->
     target_compile_features(project_options INTERFACE cxx_std_17)
     target_include_directories(project_options INTERFACE include external)

     target_compile_options(project_warnings
          INTERFACE -Wall
                    -Werror # treat all warnings as errors
                    -Wextra # reasonable and standard
                    -Wshadow # warn the user if a variable declaration shadows one from a parent context
                    -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
                    -Wold-style-cast # warn for c-style casts
                    -Wcast-align # warn for potential performance problem casts
                    -Wunused # warn on anything being unused
                    -Woverloaded-virtual # warn if you overload (not override) a virtual function
                    -Wpedantic # warn if non-standard C++ is used
                    -Wconversion # warn on type conversions that may lose data
                    -Wsign-conversion # warn on sign conversions
                    -Wnull-dereference # warn if a null dereference is detected
                    -Wdouble-promotion # warn if float is implicit promoted to double
                    -Wformat=2 # warn on security issues around functions that format output (ie printf)
     )
endif()

#----------------------------------------------------------------------------------------------
# Part till line 58 is taken from @codetechandtutorials

#           DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#----------------------------------------------------------------------------------------------

# Add locations of other CMakelists.txt (one per call)
add_subdirectory(
    src
)

# Comment out if you don't intend on using CTests
include(CTest)
enable_testing()

# Extra C++ specific options I need
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# set(CMAKE_CXX_STANDARD 17) # Set standard above for now
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Comment out if you don't need CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Define Compile Time Definitions here:
target_compile_definitions(${PROJECT_NAME} PRIVATE
     $<$<CONFIG:Debug>:DEBUG_ONLY=1>
     $<$<CONFIG:RelWithDebInfo>:DEBUG_ONLY=1>
     $<$<CONFIG:Release>:DEBUG_ONLY=0>
     $<$<CONFIG:MinSizeRel>:DEBUG_ONLY=0>
)

# Add target include directory here:
target_include_directories(${PROJECT_NAME}
    PUBLIC src
)

# Add target link directory here: (Where the Libs are)
target_link_directories(${PROJECT_NAME}
     PRIVATE src
)

# Link needed Libs:
# target_link_libraries(${PROJECT_NAME} "LIB NAME")

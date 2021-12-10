# Set CMake version number
cmake_minimum_required(VERSION 3.13)

# Change "Temp-Projekt" to your project name
project(Temp-Projekt VERSION 0.1.0)

# Add locations of other CMakelists.txt (one per call)
add_subdirectory(
    src
)

# Comment out if you don't intend on using CTests
include(CTest)
enable_testing()

# Extra C++ specific options I need
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 17)
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

# Add include directory here:
include_directories(
    PUBLIC src
)

# Add target include directory here: (I have no clue what the differance is tbh)
target_include_directories(${PROJECT_NAME}
    PUBLIC src
)

# Add target link directory here: (Where the Libs are)
target_link_directories(${PROJECT_NAME}
     PRIVATE src
)

# Link needed Libs:
# target_link_libraries(${PROJECT_NAME} "LIB NAME")

cmake_minimum_required(VERSION 3.0.0)

file(GLOB_RECURSE SRC_CXX_FILES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE SRC_C_FILES CONFIGURE_DEPENDS *.c)
file(GLOB_RECURSE INC_CXX_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include*.cpp)
file(GLOB_RECURSE INC_C_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include*.c)

# Add source files to be compiled here (should be done automatically but im making it clear if you want to add more files)
add_executable(${PROJECT_NAME}
    ${SRC_CXX_FILES}
    ${SRC_C_FILES}
    ${INC_CXX_FILES}
    ${INC_C_FILES}
)

if(UNIX AND NOT APPLE)
    # Copy Binary to DEV specified location
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        ${CMAKE_SOURCE_DIR}/bin/linux
    )

    # Delete Cmake files
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        ${CMAKE_SOURCE_DIR}/bin/linux/CMakeFiles
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_SOURCE_DIR}/bin/linux/Makefile
    )

    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove
        ${CMAKE_SOURCE_DIR}/bin/linux/cmake_install.cmake
    )

else()
    # Copy Binary to DEV specified location
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        ${CMAKE_SOURCE_DIR}/bin/${CMAKE_GENERATOR_PLATFORM} # Change this to your Prefered location (I prefer ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>/ or ${CMAKE_SOURCE_DIR}/bin/$<CMAKE_GENERATOR_PLATFORM>/)
    )
endif()

# Link assets needed for the binary to run

# add_custom_command(
# TARGET ${PROJECT_NAME} POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E create_symlink ${link_src} ${link_dst}
# DEPENDS ${link_dst}
# COMMENT "symbolic link ${link_src} => ${link_dst}"
# )
set(CMAKE_INCLUDE_CURRENT_DIR ON)
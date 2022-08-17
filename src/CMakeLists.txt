cmake_minimum_required(VERSION 3.0.0)

file(GLOB SRC_CXX_FILES *.cpp)
file(GLOB SRC_C_FILES *.c)

# Add source files to be compiled here
add_executable(${PROJECT_NAME}
    ${SRC_CXX_FILES}
    ${SRC_C_FILES}
)

message(STATUS `CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}`)

if(WIN32) # < - Windows Binary copy - >
    if(MSVC)
        # Copy Binary to DEV specified location
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}.exe
            ${CMAKE_SOURCE_DIR}/bin/
        )
    else()
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe
            ${CMAKE_SOURCE_DIR}/bin/
        )
    endif()

# # Set a symbolic link so the binary can find a required relative folder
# set(link_src "${CMAKE_SOURCE_DIR}/assets")
# if(UNIX AND NOT APPLE)
# set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/../assets")
# else()
# set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/../assets")
# endif()

# add_custom_command(
# TARGET ${PROJECT_NAME} POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E create_symlink ${link_src} ${link_dst}
# DEPENDS ${link_dst}
# COMMENT "symbolic link ${link_src} => ${link_dst}"
# )
else() # < - UNIX Binary copy - >
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/bin/
    )
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
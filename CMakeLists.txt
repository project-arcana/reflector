cmake_minimum_required(VERSION 3.8)
project(Reflector)

# =========================================
# global options


# =========================================
# define library

file(GLOB_RECURSE SOURCES "src/*.cc" "src/*.hh")

source_group("${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${SOURCES})

add_library(reflector STATIC ${SOURCES})

target_include_directories(reflector PUBLIC src/)

target_link_libraries(reflector PUBLIC
    clean-core
)

# =========================================
# set up compile flags

if (MSVC)
    target_compile_options(reflector PUBLIC /MP)
else()
    target_compile_options(reflector PRIVATE -Wall -fPIC)
    target_link_libraries(reflector PUBLIC -fuse-ld=gold)
endif()

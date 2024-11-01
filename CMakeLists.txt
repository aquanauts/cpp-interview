cmake_minimum_required(VERSION 3.15)
project(aqtc_interview VERSION 1.0 DESCRIPTION "The C++ Interview for Aquatic" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)


add_subdirectory(src)

add_compile_options(-Wall -g)

# Specific to debug mode
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
    -fno-omit-frame-pointer \
    -fsanitize=leak \
    -fsanitize=address \
    -fsanitize=undefined")

# Testing
find_package(Catch2 3 REQUIRED)
find_package(fmt REQUIRED)
add_executable(test test.cpp)
target_link_libraries(test PRIVATE Catch2::Catch2WithMain interview_lib fmt)

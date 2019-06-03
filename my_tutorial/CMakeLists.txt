cmake_minimum_required (VERSION 2.6)
project (njson_test)

add_library(njson njson.h njson.cpp)
add_executable(njson_test test.cpp)
target_link_libraries(njson_test njson)

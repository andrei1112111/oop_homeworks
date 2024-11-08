cmake_minimum_required(VERSION 3.24)
project(homework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(./)

add_library(Time_Lib SHARED mytime.h)

set_target_properties(Time_Lib PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(test)

add_executable(myTime main.cpp)

target_link_libraries(myTime PRIVATE Time_Lib)

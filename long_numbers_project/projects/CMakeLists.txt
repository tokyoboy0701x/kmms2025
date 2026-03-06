cmake_minimum_required(VERSION 3.2...3.27.5)
project(cmake_prj)

enable_testing()
add_subdirectory(long_numbers)
set(CMAKE_SUPPRESS_REGENERATION true)
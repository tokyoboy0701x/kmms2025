project(containers)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

set(CONTAINERS_LIB "containers_lib")

enable_testing()

add_library(${CONTAINERS_LIB} "")

add_subdirectory(src)
add_subdirectory(test)
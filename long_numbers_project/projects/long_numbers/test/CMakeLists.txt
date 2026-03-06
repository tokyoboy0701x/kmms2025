find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(SOURCES 
    test_long_number.cpp
)

add_executable(test_long_number ${SOURCES})

target_include_directories(test_long_number PRIVATE
    ${GTEST_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/long_numbers/src
)

target_link_libraries(test_long_number 
    ${SORT_LIB}
    ${GTEST_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

add_test(NAME test_long_number COMMAND test_long_number)
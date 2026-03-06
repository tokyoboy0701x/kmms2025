target_sources(${SORT_LIB} 
    PRIVATE
        long_number.cpp
)

target_include_directories(${SORT_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
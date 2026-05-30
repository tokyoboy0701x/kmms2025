target_sources(${CONTAINERS_LIB} 
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/doubly_linked_list.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/vector.cpp
)

target_include_directories(${CONTAINERS_LIB} PUBLIC
	${CURRENT_SOURCE_DIR}
)
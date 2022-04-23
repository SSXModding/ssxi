

add_library(ssxi
		pinebase.cpp
		ssxog.cpp
		)

# link to winsock for windows
if(WIN32)
	target_link_libraries(ssxi PUBLIC mswsock ws2_32)
endif()

target_include_directories(ssxi PUBLIC ${PROJECT_SOURCE_DIR}/include)

# :( pine doesn't have any cmake project?
# why?
target_include_directories(ssxi PRIVATE ${PROJECT_SOURCE_DIR}/third_party/pine/src)

set_target_properties(ssxi PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		)

add_library(ssxi::ssxi ALIAS ssxi)
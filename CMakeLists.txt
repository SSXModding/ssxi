cmake_minimum_required(VERSION 3.10)

# Prohibit in-source tree builds.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are strictly prohibited.")
endif()

include(cmake/Policies.cmake)

project(ssxi)

option(SSXI_BUILD_EXAMPLES "Build examples of using ssxi" OFF)


# subdirs

add_subdirectory(src/ssxi)

#if(SSXI_BUILD_EXAMPLES)
	add_subdirectory(src/examples)
#endif()


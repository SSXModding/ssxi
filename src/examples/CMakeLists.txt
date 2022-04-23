

add_executable(ssxi_test test.cpp)

set_target_properties(ssxi_test PROPERTIES
			CXX_STANDARD 20
			CXX_STANDARD_REQUIRED ON)

# link to SSXI
target_link_libraries(ssxi_test PUBLIC ssxi::ssxi)
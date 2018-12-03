

add_executable(test_hello hello.c)
target_link_libraries(test_hello uwallet_mbedtls)
target_include_directories(test_hello PRIVATE 
	$<TARGET_PROPERTY:uwallet_mbedtls,INTERFACE_INCLUDE_DIRECTORIES>
)

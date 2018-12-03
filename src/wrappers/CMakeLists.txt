
add_library(uwallet_wrappers 
	sha256.c
	sha256.h
	pbkdf2_hmac_sha512.c
	pbkdf2_hmac_sha512.h
)

target_include_directories(uwallet_wrappers PUBLIC 
 $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
PUBLIC
	$<TARGET_PROPERTY:uwallet_mbedtls,INTERFACE_INCLUDE_DIRECTORIES>
)

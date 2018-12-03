
add_library(uwallet_hdkeys 
	mnemonic.c 
	xkey.c
	wordlists.c
)

target_include_directories(uwallet_hdkeys PUBLIC 
 $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
 PRIVATE
	$<TARGET_PROPERTY:uwallet_wrappers,INTERFACE_INCLUDE_DIRECTORIES>
)

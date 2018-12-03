
add_library(uwallet_base base.c)

target_include_directories(uwallet_base PUBLIC 
 $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
 # $<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
)

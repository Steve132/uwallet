project(uwallet_mbedtls)
SET(CMAKE_AR  "gcc-ar")
SET(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
SET(CMAKE_C_ARCHIVE_FINISH   true)


set(MBEDTLS_SRCDIR "mbedtls-2.14.0")
include("mbed_sources.cmake")

add_library(uwallet_mbedtls "")

target_sources(uwallet_mbedtls PRIVATE "config_uwallet.h")
target_include_directories(uwallet_mbedtls PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(uwallet_mbedtls PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${MBEDTLS_SRCDIR}/include")
target_include_directories(uwallet_mbedtls PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${MBEDTLS_SRCDIR}/include/mbedtls")


foreach(MSRCFILE ${MBED_CRYPTO_SRCS})
	target_sources(uwallet_mbedtls PRIVATE "${MBEDTLS_SRCDIR}/library/${MSRCFILE}")
endforeach()

target_compile_definitions(uwallet_mbedtls PUBLIC -D MBEDTLS_CONFIG_FILE="config_uwallet.h")
target_compile_options(uwallet_mbedtls PUBLIC -flto)


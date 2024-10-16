# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(FRAMEWORK_SRC_DIR ${PROJECT_ROOT_DIR}/framework)
SET(FRAMEWORK_BIN_DIR ${PROJECT_BINARY_DIR}/framework)
# SET(DRIVER_SRC_DIR ${PROJECT_ROOT_DIR}/drivers)
# SET(DRIVER_BIN_DIR ${PROJECT_BINARY_DIR}/drivers)

include(${PROJECT_ROOT_DIR}/cmake/xrt.cmake)
include(${PROJECT_ROOT_DIR}/cmake/build_type.cmake)

# Policy allows setting target_link_libs for targets in other directories
# This is used by add_driver() to add in shell extensions
cmake_policy(SET CMP0079 NEW)


# Tell the linker not to embed any paths to shared libs into the exe
# By default, the embedded RPATH is searched before LD_LIBRARY_PATH.
# However, we do a lot of testing using XRT from network mounts that
# are selected by setting up LD_LIBRARY_PATH, so we need to prevent
# RPATH getting in the way.
set(CMAKE_SKIP_RPATH TRUE)


# Add coverage flags only when using GCC
# Breaks VS2019 build otherwise
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-Wall)
	
	#The following is needed to be able use inttypes.h with older versions of GLIBC
	add_compile_definitions(__STDC_FORMAT_MACROS)
endif()




if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	# Prevent deprecation warnings on older standard C functions on Windows.  We may not
	# have the "secure" variants of the functions on a target build.
	add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)

	# The following is to enable /W4. If we simply use "add_compile_options(/W4)"
	# the compiler throws warnings as /W3 is set by default (i.e we get a 
	# clash of flags)
	string(REGEX REPLACE "/W[3|4]" "/w" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

endif()

function(add_framework FRAMEWORK)
	add_subdirectory(${FRAMEWORK_SRC_DIR}/${FRAMEWORK} ${FRAMEWORK_BIN_DIR}/${FRAMEWORK})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${FRAMEWORK})
endfunction()

function(add_driver DRIVER)
	add_subdirectory(${DRIVER_SRC_DIR}/${DRIVER} ${DRIVER_BIN_DIR}/${DRIVER})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${DRIVER})
endfunction()


function(add_threads)
	find_package(Threads)
	target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
endfunction()

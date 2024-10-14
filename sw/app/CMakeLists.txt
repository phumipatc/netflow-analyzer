cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(nfa)

SET(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR}/..)
include(${PROJECT_ROOT_DIR}/cmake/common.cmake)

use_xrt()

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "nfa_exe")


add_framework(device)

# add_driver(...)

# Since this makes use of multithreading, we need to link the threads library
add_threads()
                      
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
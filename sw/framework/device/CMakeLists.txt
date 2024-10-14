
include_guard(GLOBAL)

add_library(device device.cpp
)
    
    
target_include_directories(device INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
    
    
# On Linux, we also need to link the uuid library
if(UNIX)
    find_library(UUID_LIBRARY uuid)
    target_link_libraries(device PUBLIC ${UUID_LIBRARY})
endif()
    
    
    
    
#if we are building on windows, we also need to link the stubs for the missing XRT functions
if(WIN32)
    add_subdirectory(${FRAMEWORK_SRC_DIR}/win_stubs ${FRAMEWORK_BIN_DIR}/win_stubs)
    target_link_libraries(device PRIVATE win_stubs)
endif()
    
    
# Following functions add XRT libraries and headers to the build
add_xrt_libs(device)
add_xrt_include(device)
function(use_xrt)
    if (NOT "$ENV{XILINX_XRT}" STREQUAL "")
        set(XILINX_XRT "$ENV{XILINX_XRT}" PARENT_SCOPE)
    else()
        message(FATAL_ERROR "XILINX_XRT environment variable not set")
    endif()
endfunction()

# function adds XRT libraries to ${TARGET} build
function(add_xrt_libs TARGET)
    if ("${XILINX_XRT}" STREQUAL "")
        message(FATAL_ERROR "XILINX_XRT not set")
    endif()

    set(XRT_LIB_CORE xrt_core)

    find_library(XRT_CORE ${XRT_LIB_CORE} ${XILINX_XRT}/lib)
    find_library(XRT_UTIL xrt_coreutil ${XILINX_XRT}/lib)

    target_link_libraries(${TARGET} PUBLIC ${XRT_CORE} ${XRT_UTIL})
endfunction()





# function adds XRT headers to ${TARGET} build
function(add_xrt_include TARGET)
    if ("${XILINX_XRT}" STREQUAL "")
        message(FATAL_ERROR "XILINX_XRT not set")
    endif()

    target_include_directories(${TARGET} PUBLIC "${XILINX_XRT}/include")
endfunction()

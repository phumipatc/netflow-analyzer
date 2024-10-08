# SPDX-License-Identifier: Apache-2.0
# Copyright (C) 2019-2021 Xilinx, Inc. All rights reserved.
# Copyright (C) 2023 Advanced Micro Devices, Inc. All rights reserved.

# Get the branch
execute_process(
  COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${XRT_SOURCE_DIR}
  OUTPUT_VARIABLE XRT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND ${GIT_EXECUTABLE} rev-parse --verify HEAD
  WORKING_DIRECTORY ${XRT_SOURCE_DIR}
  OUTPUT_VARIABLE XRT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get number of commits for HEAD
execute_process(
  COMMAND ${GIT_EXECUTABLE} rev-list --count HEAD
  WORKING_DIRECTORY ${XRT_SOURCE_DIR}
  OUTPUT_VARIABLE XRT_HEAD_COMMITS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get number of commits between HEAD and master
execute_process(
  COMMAND ${GIT_EXECUTABLE} rev-list --count HEAD ^origin/master
  WORKING_DIRECTORY ${XRT_SOURCE_DIR}
  OUTPUT_VARIABLE XRT_BRANCH_COMMITS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash date of the working branch
execute_process(
  COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%cD
  WORKING_DIRECTORY ${XRT_SOURCE_DIR}
  OUTPUT_VARIABLE XRT_HASH_DATE
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get all of the modified files in the current git environment
execute_process(
  COMMAND ${GIT_EXECUTABLE} status --porcelain -u no
  WORKING_DIRECTORY ${XRT_SOURCE_DIR}
  OUTPUT_VARIABLE XRT_MODIFIED_FILES
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REPLACE "\n" "," XRT_MODIFIED_FILES "${XRT_MODIFIED_FILES}")

# Get the build date RFC format
execute_process(
  COMMAND date -R
  WORKING_DIRECTORY ${XRT_SOURCE_DIR}
  OUTPUT_VARIABLE XRT_DATE_RFC
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(TIMESTAMP XRT_DATE "%Y-%m-%d %H:%M:%S")

configure_file(
  ${XRT_SOURCE_DIR}/CMake/config/version.h.in
  ${XRT_BINARY_DIR}/gen/version.h
)

configure_file(
  ${XRT_SOURCE_DIR}/CMake/config/version.json.in
  ${XRT_BINARY_DIR}/gen/version.json
)

install(FILES ${XRT_BINARY_DIR}/gen/version.h DESTINATION ${XRT_INSTALL_INCLUDE_DIR})
if (${XRT_NATIVE_BUILD} STREQUAL "yes")
install(FILES ${XRT_BINARY_DIR}/gen/version.json DESTINATION ${XRT_INSTALL_DIR})
endif()

# This is not required on MPSoC platform. To avoid yocto error, do NOT intall
if ((${XRT_NATIVE_BUILD} STREQUAL "yes") AND (NOT WIN32))
  # Copied over from dkms.cmake. TODO: cleanup
  set (XRT_DKMS_INSTALL_DIR "/usr/src/xrt-${XRT_VERSION_STRING}")
  install(FILES ${XRT_BINARY_DIR}/gen/version.h DESTINATION ${XRT_DKMS_INSTALL_DIR}/driver/include)
endif()

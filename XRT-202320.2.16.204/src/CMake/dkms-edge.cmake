# SPDX-License-Identifier: Apache-2.0
# Copyright (C) 2019-2022 Xilinx, Inc. All rights reserved.
#
# Custom variables imported by this CMake stub which should be defined by parent CMake:
# XRT_DKMS_DRIVER_SRC_BASE_DIR

set (XRT_DKMS_INSTALL_DIR "/usr/src/xrt-${XRT_VERSION_STRING}")
set (XRT_DKMS_INSTALL_DRIVER_DIR "${XRT_DKMS_INSTALL_DIR}/driver")

message("-- XRT DRIVER SRC BASE DIR ${XRT_DKMS_DRIVER_SRC_BASE_DIR}")

SET (DKMS_FILE_NAME "dkms.conf")
SET (DKMS_POSTINST "postinst-edge")
SET (DKMS_PRERM "prerm-edge")

configure_file (
  "${XRT_SOURCE_DIR}/CMake/config/dkms-zocl/${DKMS_FILE_NAME}.in"
  ${DKMS_FILE_NAME}
  @ONLY
  )

configure_file (
  "${XRT_SOURCE_DIR}/CMake/config/${DKMS_POSTINST}.in"
  "postinst"
  @ONLY
  )

configure_file (
  "${XRT_SOURCE_DIR}/CMake/config/${DKMS_PRERM}.in"
  "prerm"
  @ONLY
  )

SET (XRT_DKMS_DRIVER_SRC_DIR ${XRT_DKMS_DRIVER_SRC_BASE_DIR}/edge/drm)
SET (XRT_DKMS_DRIVER_INCLUDE_DIR ${XRT_DKMS_DRIVER_SRC_BASE_DIR}/edge/drm)
SET (XRT_DKMS_CORE_DIR ${XRT_DKMS_DRIVER_SRC_BASE_DIR})
SET (XRT_DKMS_CORE_COMMON_DRV ${XRT_DKMS_CORE_DIR}/common/drv)

SET (XRT_DKMS_DRIVER_SRCS
  zocl/include/sched_exec.h
  zocl/include/zocl_aie.h
  zocl/include/zocl_bo.h
  zocl/include/zocl_cu.h
  zocl/include/zocl_cu_xgq.h
  zocl/include/zocl_dma.h
  zocl/include/zocl_drv.h
  zocl/include/zocl_error.h
  zocl/include/zocl_ert.h
  zocl/include/zocl_ert_intc.h
  zocl/include/zocl_generic_cu.h
  zocl/include/zocl_ioctl.h
  zocl/include/zocl_lib.h
  zocl/include/zocl_mailbox.h
  zocl/include/zocl_ospi_versal.h
  zocl/include/zocl_sk.h
  zocl/include/zocl_util.h
  zocl/include/zocl_watchdog.h
  zocl/include/zocl_xclbin.h
  zocl/include/zocl_xgq.h
  zocl/include/zocl_xgq_plat.h
  zocl/10-zocl.rules
  zocl/cu.c
  zocl/cu_scu.c
  zocl/LICENSE
  zocl/Makefile
  zocl/zocl_aie.c
  zocl/zocl_bo.c
  zocl/zocl_csr_intc.c
  zocl/zocl_ctrl_ert.c
  zocl/zocl_cu.c
  zocl/zocl_cu_xgq.c
  zocl/zocl_dma.c
  zocl/zocl_drv.c
  zocl/zocl_error.c
  zocl/zocl_ert.c
  zocl/zocl_ioctl.c
  zocl/zocl_kds.c
  zocl/zocl_lib.c
  zocl/zocl_mailbox.c
  zocl/zocl_ospi_versal.c
  zocl/zocl_ov_sysfs.c
  zocl/zocl_sk.c
  zocl/zocl_rpu_channel.c
  zocl/zocl_sk.c
  zocl/zocl_sysfs.c
  zocl/zocl_watchdog.c
  zocl/zocl_xclbin.c
  zocl/zocl_xgq.c
  zocl/zocl_xgq_intc.c
  )

# includes relative to core
SET (XRT_DKMS_CORE_INCLUDES
  include/ert.h
  include/ps_kernel.h
  include/types.h
  include/xclfeatures.h
  include/xclbin.h
  include/xclerr.h
  include/xclerr_int.h
  include/xclhal2_mem.h
  include/xrt_error_code.h
  include/xrt_mem.h
  include/xgq_cmd_common.h
  include/xgq_cmd_ert.h
  include/xgq_cmd_vmr.h
  include/xgq_impl.h
  include/xgq_resp_parser.h
  )

SET (XRT_DKMS_COMMON_XRT_DRV
  common/drv/cu_hls.c
  common/drv/fast_adapter.c
  common/drv/kds_hwctx.c
  common/drv/kds_core.c
  common/drv/Makefile
  common/drv/xgq_execbuf.c
  common/drv/xrt_cu.c
  common/drv/xrt_xclbin.c
  )

SET (XRT_DKMS_COMMON_XRT_DRV_INCLUDES
  common/drv/include/cu_xgq.h
  common/drv/include/kds_client.h
  common/drv/include/kds_command.h
  common/drv/include/kds_core.h
  common/drv/include/kds_hwctx.h
  common/drv/include/kds_ert_table.h
  common/drv/include/kds_stat.h
  common/drv/include/xgq_execbuf.h
  common/drv/include/xrt_cu.h
  common/drv/include/xrt_drv.h
  common/drv/include/xrt_ert.h
  common/drv/include/xrt_xclbin.h
  )

SET (XRT_DKMS_CORE_EDGE_INCLUDES
  edge/include/zynq_ioctl.h
  )

foreach (DKMS_FILE ${XRT_DKMS_DRIVER_SRCS})
  get_filename_component(DKMS_DIR ${DKMS_FILE} DIRECTORY)
  install (FILES ${XRT_DKMS_DRIVER_SRC_DIR}/${DKMS_FILE} DESTINATION ${XRT_DKMS_INSTALL_DRIVER_DIR}/${DKMS_DIR})
endforeach()

foreach (DKMS_FILE ${XRT_DKMS_CORE_INCLUDES})
  get_filename_component(DKMS_DIR ${DKMS_FILE} DIRECTORY)
  install (FILES ${XRT_DKMS_CORE_DIR}/${DKMS_FILE} DESTINATION ${XRT_DKMS_INSTALL_DRIVER_DIR}/zocl/${DKMS_DIR})
endforeach()

foreach (DKMS_FILE ${XRT_DKMS_COMMON_XRT_DRV})
  install (FILES ${XRT_DKMS_CORE_DIR}/${DKMS_FILE} DESTINATION ${XRT_DKMS_INSTALL_DRIVER_DIR}/common/)
endforeach()

foreach (DKMS_FILE ${XRT_DKMS_COMMON_XRT_DRV_INCLUDES})
  install (FILES ${XRT_DKMS_CORE_DIR}/${DKMS_FILE} DESTINATION ${XRT_DKMS_INSTALL_DRIVER_DIR}/zocl/include/)
endforeach()

foreach (DKMS_FILE ${XRT_DKMS_CORE_EDGE_INCLUDES})
  install (FILES ${XRT_DKMS_CORE_DIR}/${DKMS_FILE} DESTINATION ${XRT_DKMS_INSTALL_DRIVER_DIR}/zocl/include/)
endforeach()

install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${DKMS_FILE_NAME} DESTINATION ${XRT_DKMS_INSTALL_DIR})

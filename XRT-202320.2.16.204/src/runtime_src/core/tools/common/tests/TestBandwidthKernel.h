// SPDX-License-Identifier: Apache-2.0
// Copyright (C) 2023 Advanced Micro Devices, Inc. All rights reserved.

#ifndef __TestBandwidthKernel_h_
#define __TestBandwidthKernel_h_

#include "tools/common/TestRunner.h"

class TestBandwidthKernel : public TestRunner {
  public:
    boost::property_tree::ptree run(std::shared_ptr<xrt_core::device> dev);

  public:
    TestBandwidthKernel();
};

#endif

//==----- feature_test.hpp - SYCL Feature Test Definitions -----*- C++ -*---==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// ===--------------------------------------------------------------------=== //

//
// IMPORTANT:  feature_test.hpp is a generated file - DO NOT EDIT
//             original definitions are in feature_test.hpp.in
//

#pragma once

#include <sycl/detail/defines_elementary.hpp>

namespace sycl {
inline namespace _V1 {

#ifdef __clang__
#ifndef __has_extension
#define __has_extension(x) 0
#endif
#endif

#define SYCL_BACKEND_OPENCL 1

// Feature test macro definitions

// TODO: Move these feature-test macros to compiler driver.
#define SYCL_EXT_INTEL_DEVICE_INFO 6
#define SYCL_EXT_ONEAPI_DEVICE_ARCHITECTURE 1
#define SYCL_EXT_ONEAPI_SUB_GROUP_MASK 2
#define SYCL_EXT_ONEAPI_LOCAL_MEMORY 1
#define SYCL_EXT_ONEAPI_MATRIX 1
#define SYCL_EXT_ONEAPI_ASSERT 1
#define SYCL_EXT_ONEAPI_COMPLEX_ALGORITHMS 1
#define SYCL_EXT_ONEAPI_DISCARD_QUEUE_EVENTS 1
#define SYCL_EXT_ONEAPI_QUEUE_PRIORITY 1
#define SYCL_EXT_ONEAPI_ENQUEUE_BARRIER 1
#define SYCL_EXT_ONEAPI_FREE_FUNCTION_QUERIES 1
#define SYCL_EXT_ONEAPI_BINDLESS_IMAGES 1
#define SYCL_EXT_ONEAPI_GROUP_ALGORITHMS 1
#define SYCL_EXT_ONEAPI_GROUP_SORT 1
#define SYCL_EXT_ONEAPI_KERNEL_COMPILER 1
#define SYCL_EXT_ONEAPI_KERNEL_COMPILER_OPENCL 1
#define SYCL_EXT_ONEAPI_KERNEL_COMPILER_SPIRV 1
#define SYCL_EXT_ONEAPI_MAX_WORK_GROUP_QUERY 1
#define SYCL_EXT_ONEAPI_ND_RANGE_REDUCTIONS 1
#define SYCL_EXT_ONEAPI_DEFAULT_CONTEXT 1
#define SYCL_EXT_ONEAPI_USE_PINNED_HOST_MEMORY_PROPERTY 1
#define SYCL_EXT_ONEAPI_ROOT_GROUP 1
#define SYCL_EXT_ONEAPI_SRGB 1
#define SYCL_EXT_ONEAPI_SUB_GROUP 1
#define SYCL_EXT_ONEAPI_PROPERTIES 1
#define SYCL_EXT_ONEAPI_NATIVE_MATH 1
#define SYCL_EXT_ONEAPI_BFLOAT16_MATH_FUNCTIONS 1
#define SYCL_EXT_ONEAPI_COMPOSITE_DEVICE 1
#define SYCL_EXT_INTEL_DATAFLOW_PIPES 1
#ifdef __clang__
#if __has_extension(sycl_extended_atomics)
#define SYCL_EXT_INTEL_EXTENDED_ATOMICS 1
#endif
#endif
#define SYCL_EXT_INTEL_FPGA_DEVICE_SELECTOR 3
#define SYCL_EXT_INTEL_FPGA_KERNEL_INTERFACE_PROPERTIES 1
#define SYCL_EXT_INTEL_FPGA_LSU 1
#define SYCL_EXT_INTEL_FPGA_REG 1
#define SYCL_EXT_INTEL_KERNEL_ARGS_RESTRICT 1
#define SYCL_EXT_INTEL_MEM_CHANNEL_PROPERTY 1
#define SYCL_EXT_INTEL_USM_ADDRESS_SPACES 2
#define SYCL_EXT_INTEL_RUNTIME_BUFFER_LOCATION 1
#define SYCL_EXT_INTEL_QUEUE_INDEX 1
#define SYCL_EXT_INTEL_FPGA_MEM 1
#define SYCL_EXT_INTEL_FPGA_DATAPATH 1
#define SYCL_EXT_ONEAPI_AUTO_LOCAL_RANGE 1
#define SYCL_EXT_ONEAPI_BACKEND_LEVEL_ZERO 5
#define SYCL_EXT_ONEAPI_USM_DEVICE_READ_ONLY 1
#define SYCL_EXT_ONEAPI_KERNEL_PROPERTIES 1
#define SYCL_EXT_ONEAPI_QUEUE_EMPTY 1
#define SYCL_EXT_ONEAPI_USER_DEFINED_REDUCTIONS 1
#define SYCL_EXT_ONEAPI_WEAK_OBJECT 1
#define SYCL_EXT_ONEAPI_MEMCPY2D 1
#define SYCL_EXT_ONEAPI_KERNEL_ARG_PROPERTIES 1
#define SYCL_EXT_ONEAPI_ANNOTATED_ARG 1
#define SYCL_EXT_ONEAPI_ANNOTATED_PTR 1
#define SYCL_EXT_ONEAPI_COPY_OPTIMIZE 1
#define SYCL_EXT_ONEAPI_USM_MALLOC_PROPERTIES 1
#define SYCL_ENABLE_KERNEL_FUSION 0
#if SYCL_ENABLE_KERNEL_FUSION
#define SYCL_EXT_CODEPLAY_KERNEL_FUSION 1
#endif
#define SYCL_EXT_INTEL_CACHE_CONFIG 1
#define SYCL_EXT_ONEAPI_GRAPH 1
#define SYCL_EXT_CODEPLAY_MAX_REGISTERS_PER_WORK_GROUP_QUERY 1
#define SYCL_EXT_ONEAPI_DEVICE_GLOBAL 1
#define SYCL_EXT_INTEL_QUEUE_IMMEDIATE_COMMAND_LIST 1
#define SYCL_EXT_ONEAPI_PREFETCH 1
#define SYCL_EXT_INTEL_CACHE_CONTROLS 1
#define SYCL_EXT_INTEL_FP_CONTROL 1
#define SYCL_EXT_ONEAPI_NON_UNIFORM_GROUPS 1
#define SYCL_EXT_ONEAPI_IN_ORDER_QUEUE_EVENTS 1
#define SYCL_EXT_INTEL_MATRIX 1
#define SYCL_EXT_INTEL_FPGA_TASK_SEQUENCE 1

#ifndef __has_include
#define __has_include(x) 0
#endif

#if __has_include("detail/plugins/cuda/features.hpp")
#include "detail/plugins/cuda/features.hpp"
#endif

#if __has_include("detail/plugins/hip/features.hpp")
#include "detail/plugins/hip/features.hpp"
#endif

} // namespace _V1
} // namespace sycl

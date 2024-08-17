//==------- common_info.hpp ----- Common SYCL info methods------------------==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#pragma once
#include <sycl/detail/export.hpp>

#include <string>
#include <vector>

namespace sycl {
inline namespace _V1 {
namespace detail {

std::vector<std::string> __SYCL_EXPORT split_string(const std::string &str,
                                                    char delimeter);

} // namespace detail
} // namespace _V1
} // namespace sycl

#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>
#include <vector>
#include <array>
#include "aligned_vector.hpp"

template<typename T> concept FloatType = std::is_floating_point_v<T>;

// no overflow handler
template<FloatType T> T average(const aligned_vector<T>& lists);

// no overflow handler
template<FloatType T> T variance(const aligned_vector<T>& lists);

#if defined __COMPILER_MSVC__
#   include "header_msvc.ipp"
#elif defined (__COMPILER_GCC__) || (__COMPILER_CLANG__)
#   include "header_cl_gcc.ipp"
#endif

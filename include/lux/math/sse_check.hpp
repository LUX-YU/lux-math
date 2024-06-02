#pragma once

#if defined __COMPILER_MSVC__
#   include <intrin.h>
    static inline bool __check_sse_support() {int cpuInfo[4]; __cpuid(cpuInfo, 1); return (cpuInfo[3] & (1 << 25)) != 0;}
#elif defined (__COMPILER_GCC__) || (__COMPILER_CLANG__)
#   include <cpuid.h>
    static inline bool __check_sse_support() {unsigned int eax, ebx, ecx, edx; __get_cpuid(1, &eax, &ebx, &ecx, &edx); return (edx & bit_SSE) != 0;}
#endif

static const inline bool __support_sse = __check_sse_support();

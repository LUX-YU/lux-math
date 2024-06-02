#include <cpuid.h>

static inline bool __check_sse_support() {unsigned int eax, ebx, ecx, edx; __get_cpuid(1, &eax, &ebx, &ecx, &edx); return (edx & bit_SSE) != 0;}


#include <intrin.h>
#include <numeric>
#include "sse_check.hpp"

template<typename U, FloatType T = double>
T __average_sse(const aligned_vector<U>& lists)
{
    const size_t array_size = lists.size();
    const U*     data       = lists.data();
    // float  4
    // double 2
    static constexpr char block_size = (128 / 8) / sizeof(U);
    static_assert(block_size == 4 || block_size == 2, "unsupport block size.");

    const size_t blocks    = array_size / block_size;
    const size_t remainder = array_size % block_size;

    __m128 sum = _mm_setzero_ps();
    for(size_t i = 0; i < blocks; i++)
    {
        __m128 temp = _mm_load_ps(&data[i * block_size]);
        sum = _mm_add_ps(sum, temp);
    }

    T remainder_sum = 0.0f;
    for (size_t i = array_size - remainder; i < size; i++) {
        remainder_sum += data[i];
    }

    T final_sum[block_size];
    T return_sum;
    _mm_store_ps(final_sum, sum);
    if constexpr(block_size == 4)
    {
        return_sum = final_sum[0] + final_sum[1] + final_sum[2] + final_sum[3] + remainder_sum;
    }
    else if constexpr(block_size == 2)
    {
        return_sum = final_sum[0] + final_sum[1] + remainder_sum;
    }

    return return_sum / array_size;
}

template<FloatType T> 
T __average(const aligned_vector<T>& lists)
{
    return std::accumulate(lists.begin(), lists.end(), 0) / lists.size();
}

template<FloatType T> 
T average(const aligned_vector<T>& lists)
{
    if(__support_sse) return __average_sse(lists);
    return __average(lists);
}

template<FloatType T>
T variance(const aligned_vector<T>& lists)
{
    
}

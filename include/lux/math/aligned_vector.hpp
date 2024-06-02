#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include <immintrin.h>

template <typename T, std::size_t Alignment = 16>
class __aligned_allocator {
public:
    using value_type = T;

    template <class U>
    struct rebind
    {
        using other = __aligned_allocator<U>;
    };

    T* allocate(std::size_t n) {
        void* ptr = _mm_malloc(n * sizeof(T), Alignment);
        if (!ptr) {
            throw std::bad_alloc();
        }
        return static_cast<T*>(ptr);
    }

    void deallocate(T* ptr, std::size_t /*n*/) noexcept {
        _mm_free(ptr);
    }
};

template<class T> using aligned_vector = std::vector<T, __aligned_allocator<T>>;

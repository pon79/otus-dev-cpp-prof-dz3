#pragma once

#include <type_traits>
#include <memory>

template<class T>
class MyAllocator
{
    static_assert (!std::is_same_v<T,void>);
public:
    MyAllocator() = default;

    using value_type = T;

    T *allocate( std::size_t n ) {

        if( n == 0u )
            return nullptr;

        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, [[maybe_unused]] std::size_t n) {
        std::free(p);
    }

//    template <class U, class... Args>
//    void construct(U *p, Args &&...args) {
//        new (p) U(std::forward<Args>(args)...);
//    };

//    template <typename U>
//	void destroy(U *p) {
//		p->~U();
//	}
};

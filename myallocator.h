#pragma once

#include <type_traits>
#include <iostream>
#include <memory>

template<class T, int N>
class MyAllocator
{
    T* m_p;        // use reserve
    size_t m_step; // the number of elements released at a time
    size_t m_size;
    size_t m_max_size;

    static_assert (!std::is_same_v<T,void>);
public:
    MyAllocator() : m_p{ nullptr}, m_step{N}, m_size{0}, m_max_size{0} { }

    using pointer = T *;
    using value_type = T;
    using reference = T &;
    using const_pointer = const T *;
    using const_reference = const T &;

    template <class U, int M>
    struct rebind {
        using other = MyAllocator<U, M>;
    };

    T *allocate( std::size_t new_max_size ) {

//        std::cout << "new_max_size: " << n << std::endl;

        if( new_max_size < m_max_size )
            return m_p;

        T *p = std::malloc((new_max_size > N ? new_max_size : N) * sizeof(T));
        if (!p)
            throw std::bad_alloc();

        for( size_t index{0}; index < m_size ; ++index) {
            p[index] = std::move( m_p[index] );
        }

        for( size_t index{0}; index < m_size ; ++index) {
            destroy( &m_p[index] );
        }

        m_max_size = new_max_size;

        m_p = reinterpret_cast<T *>(p);

        return m_p;
    }

    void deallocate(T *p, [[maybe_unused]] std::size_t n) {
        std::cout << "deallocate" << std::endl;
        std::free(p);
    }

    template <class U, class... Args>
    void construct(U *p, Args &&...args) {
        ++m_size;
        new ( (void*) p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U *p) {
        --m_size;
        std::cout << "m_size: " << m_size << std::endl;
        p->~U();
    }

    constexpr size_t max_size(){ return m_max_size; }
};

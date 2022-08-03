#pragma once

#include <type_traits>
#include <iostream>
#include <memory>

template<class T>
class MyAllocator
{
    T* m_p;
    size_t m_size{0};
    size_t m_max_size{0};

    static_assert (!std::is_same_v<T,void>);
public:
    MyAllocator() = default;

    using value_type = T;

    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;

    template <typename U>
    struct rebind {
        using other = MyAllocator<U>;
    };

    T *allocate( std::size_t n ) {

        if( n == 0u )
            return nullptr;

        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();

        m_max_size = n;

        m_p = reinterpret_cast<T *>(p);

        return m_p;
    }

    void deallocate(T *p, [[maybe_unused]] std::size_t n) {
        std::cout << "deallocate" << std::endl;
        std::free(p);
    }

    void reserve( std::size_t new_max_size) {

        std::cout << "new_max_size: " << new_max_size << std::endl;

        if( new_max_size <= m_max_size )
            return ;

        T* p = allocate( new_max_size );

        for( size_t index{0}; index < m_size ; ++index) {
            p[index] = std::move( m_p[index] );
        }

        for( size_t index{0}; index < m_size ; ++index) {
            destroy( m_p[index] );
        }

        m_max_size = new_max_size;

        m_p = p;
    }

    template <class U, class... Args>
    void construct(U *p, Args &&...args) {
        ++m_size;
        new (p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U *p) {
        --m_size;
        std::cout << "m_size: " << m_size << std::endl;
        p->~U();
    }

};

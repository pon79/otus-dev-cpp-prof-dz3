#pragma once

#include "myallocator.h"

template <class T, class A = MyAllocator<T>>
class MyVector
{
    A alloc;

    int m_size;
    T* m_elem;
    int m_capacity;
public:
    MyVector(): m_size{0}, m_elem{nullptr}, m_capacity{0} {}

    explicit MyVector(int size): m_size{size}, m_elem{new T[size]}, m_capacity{size} {}

//    // copy
//    MyVector(const MyVector&);
//    MyVector& operator=(const MyVector& a);

//    // move
//    MyVector(const MyVector&&);
//    MyVector& operator=(const MyVector&&);

//    ~MyVector() { delete[] m_elem; }
        ~MyVector() { alloc.deallocate(m_elem, m_capacity); }

    T& operator[ ](int index){ return m_elem[index]; }
    const T& operator[ ](int index) const { return m_elem[index]; }

    int size() const { return m_size; }
    int capacity() const { return m_capacity; }

    void reserve( int newalloc) {

        m_elem = alloc.reserve(newalloc);

        if(m_elem)
            m_capacity = newalloc;
    }

//    void resize( int newsize);
    void push_back( const T& value) {
        if( m_capacity == 0 ) {
            reserve( 8 );
        } else if( m_size == m_capacity ) {
            reserve( m_capacity * 2 );
        }
        alloc.construct( &m_elem[ m_size ], value );
        ++m_size;
    }
};

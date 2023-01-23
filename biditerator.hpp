#ifndef BID_ITERATOR_H
#define BID_ITERATOR_H

#pragma once

#include "iterators.hpp"
#include <iterator>

namespace ft
{
    template <class T>
    struct bidirectional_iterator 
    {
        typedef std::size_t size_type;
        typedef T       iterator_type;
        typedef ft::iterator_traits<T> traits;
        typedef typename traits::value_type value_type;
        typedef typename traits::difference_type difference_type;
        typedef typename traits::pointer pointer;
        typedef typename traits::reference reference;
        typedef typename std::bidirectional_iterator_tag iterator_category;

        // Iterator() : _m_ptr(iterator_type()) {}

        bidirectional_iterator(pointer ptr = pointer()) : _m_ptr(ptr) { }
       
        bidirectional_iterator(const bidirectional_iterator &iter) : _m_ptr(iter._m_ptr) {}
       
       //bidirectional_iterator Assignment operator
        bidirectional_iterator& operator=(const bidirectional_iterator &iter) { _m_ptr = iter._m_ptr; return *this;}

        ~bidirectional_iterator() {}

        pointer base(void) const { return this->_m_ptr; }

        reference operator*(void) { return (*_m_ptr); }
        pointer operator->() const { return (_m_ptr); }

        // Input bidirectional_iterator Incrementation
        bidirectional_iterator &operator++(void)
        {
            ++_m_ptr;
            return (*this);
        }
        bidirectional_iterator &operator--(void)
        {
            --_m_ptr;
            return (*this);
        }

        bidirectional_iterator operator++(int)
        {
            bidirectional_iterator temp(*this);
            ++_m_ptr;
            return temp;
        }
        bidirectional_iterator operator--(int)
        {
            bidirectional_iterator temp(*this);
            --_m_ptr;
            return temp;
        }
   
    protected:
        pointer _m_ptr;
    };

      template<class T>
    inline bool operator==(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }

    template<class T, class L>
    inline bool operator==(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<L> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }
    
    template<class T>
    inline bool operator!=(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

    template<class T, class L>
    inline bool operator!=(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<L> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

    template<class T>
    inline bool operator<(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs) 
    {
            return (lhs.base() < rhs.base());
    }

    template<class T, class L>
    inline bool operator<(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<L> &rhs) 
    {
            return (lhs.base() < rhs.base());
    }

    template<class T>
    inline bool operator>(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs) 
    {
            return (lhs.base() > rhs.base());
    }

    template<class T, class L>
    inline bool operator>(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<L> &rhs) 
    {
            return (lhs.base() > rhs.base());
    }

    template<class T>
    inline bool operator<=(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs) 
    {
            return (lhs.base() <= rhs.base());
    }

    template<class T, class L>
    inline bool operator<=(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<L> &rhs) 
    {
            return (lhs.base() <= rhs.base());
    }

    template<class T>
    inline bool operator>=(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs) 
    {
            return (lhs.base() >= rhs.base());
    }

    template<class T, class L>
    inline bool operator>=(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<L> &rhs) 
    {
            return (lhs.base() >= rhs.base());
    }

    template<class T>
    inline typename bidirectional_iterator<T>::difference_type 
    operator+(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs)
    {
            return (lhs.base() + rhs.base());
    }

    template<class T, class L>
    inline typename bidirectional_iterator<T>::difference_type 
    operator+(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<L> &rhs)
    {
            return (lhs.base() + rhs.base());
    }

    template<class T>
    inline typename bidirectional_iterator<T>::difference_type 
    operator-(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<T> &rhs)
    {
            return (lhs.base() - rhs.base());
    }

    template<class T, class L>
    inline typename bidirectional_iterator<T>::difference_type 
    operator-(const bidirectional_iterator<T> &lhs, const bidirectional_iterator<L> &rhs)
    {
            return (lhs.base() - rhs.base());
    }

    template<class T>
    inline bidirectional_iterator<T> operator+(int n, const bidirectional_iterator<T> &rhs)
    {
        return bidirectional_iterator<T>(rhs.base() + n);
    }

}
#endif
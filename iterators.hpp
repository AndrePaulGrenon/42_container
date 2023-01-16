#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "Iterator_traits.hpp"
#include <iostream>
#include <cstddef>
#include <iterator>

namespace ft
{

#if defined(_LIBCPP_ITERATOR) || defined(_STL_ITERATOR_H)

    typedef std::input_iterator_tag input_iterator_tag;
    typedef std::output_iterator_tag output_iterator_tag;
    typedef std::forward_iterator_tag forward_iterator_tag;
    typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
    typedef std::random_access_iterator_tag random_access_iterator_tag;

#else

    struct input_iterator_tag
    {
    };
    struct output_iterator_tag
    {
    };
    struct forward_iterator_tag
    {
    } : input_iterator_tag{};
    struct bidirectional_iterator_tag
    {
    } : forward_iterator_tag{};
    struct random_access_iterator_tag
    {
    } : bidirectional_iterator_tag{};

#endif

    template <class Category, class T, class Distance = std::ptrdiff_t,
              class Pointer = T *, class Reference = T &>
    class Iterator_base
    {
    public:
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;

    private:
    };

    template <typename T>
    struct IteratorTraits
    {
        // Define the types for the iterator's value, difference, pointer, and reference.
        typedef T value_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        // Specify the iterator category as std::random_access_iterator_tag.
        typedef random_access_iterator_tag iterator_category;
    };


    template <class T>
    struct Iterator
    {

        typedef std::size_t size_type;
        typedef T       iterator_type;
        typedef IteratorTraits<T> traits;
        typedef typename traits::value_type value_type;
        typedef typename traits::difference_type difference_type;
        typedef typename traits::pointer pointer;
        typedef typename traits::reference reference;
        typedef typename traits::iterator_category iterator_category;

        // Iterator() : _m_ptr(iterator_type()) {}

        Iterator(pointer ptr = pointer()) : _m_ptr(ptr) { }
       
        Iterator(const Iterator &iter) : _m_ptr(iter._m_ptr) {}
       
       //Iterator Assignment operator
        Iterator& operator=(const Iterator &iter) { _m_ptr = iter._m_ptr; return *this;}

        ~Iterator() {}

        pointer base(void) const { return this->_m_ptr; }

        reference operator*(void) { return (*_m_ptr); }
        pointer operator->() const { return (_m_ptr); }

        // Input Iterator Incrementation
        Iterator &operator++(void)
        {
            ++_m_ptr;
            return (*this);
        }
        Iterator &operator--(void)
        {
            --_m_ptr;
            return (*this);
        }

        Iterator operator++(int)
        {
            Iterator temp(*this);
            ++_m_ptr;
            return temp;
        }
        Iterator operator--(int)
        {
            Iterator temp(*this);
            --_m_ptr;
            return temp;
        }
   
        reference operator[](size_type n) const
        {
            return _m_ptr[n];
        }

       //Random access incrementation

        Iterator &operator+=(size_type n)
        {
            this->_m_ptr += n;
            return (*this);
        }
        Iterator &operator-=(size_type n)
        {
            this->_m_ptr -= n;
            return (*this);
        }

        Iterator operator+(difference_type n) const
        {
            return Iterator(_m_ptr + n);
        }
        Iterator operator-(difference_type n) const
        {
            return Iterator(_m_ptr - n);
        }
        
    protected:
        pointer _m_ptr;
    };


    // COMPARISON OPERATORS

    template<class T>
    inline bool operator==(const Iterator<T> &lhs, const Iterator<T> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }

    template<class T, class L>
    inline bool operator==(const Iterator<T> &lhs, const Iterator<L> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }
    
    template<class T>
    inline bool operator!=(const Iterator<T> &lhs, const Iterator<T> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

    template<class T, class L>
    inline bool operator!=(const Iterator<T> &lhs, const Iterator<L> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

    template<class T>
    inline bool operator<(const Iterator<T> &lhs, const Iterator<T> &rhs) 
    {
            return (lhs.base() < rhs.base());
    }

    template<class T, class L>
    inline bool operator<(const Iterator<T> &lhs, const Iterator<L> &rhs) 
    {
            return (lhs.base() < rhs.base());
    }

    template<class T>
    inline bool operator>(const Iterator<T> &lhs, const Iterator<T> &rhs) 
    {
            return (lhs.base() > rhs.base());
    }

    template<class T, class L>
    inline bool operator>(const Iterator<T> &lhs, const Iterator<L> &rhs) 
    {
            return (lhs.base() > rhs.base());
    }

    template<class T>
    inline bool operator<=(const Iterator<T> &lhs, const Iterator<T> &rhs) 
    {
            return (lhs.base() <= rhs.base());
    }

    template<class T, class L>
    inline bool operator<=(const Iterator<T> &lhs, const Iterator<L> &rhs) 
    {
            return (lhs.base() <= rhs.base());
    }

    template<class T>
    inline bool operator>=(const Iterator<T> &lhs, const Iterator<T> &rhs) 
    {
            return (lhs.base() >= rhs.base());
    }

    template<class T, class L>
    inline bool operator>=(const Iterator<T> &lhs, const Iterator<L> &rhs) 
    {
            return (lhs.base() >= rhs.base());
    }

    template<class T>
    inline typename Iterator<T>::difference_type 
    operator+(const Iterator<T> &lhs, const Iterator<T> &rhs)
    {
            return (lhs.base() + rhs.base());
    }

    template<class T, class L>
    inline typename Iterator<T>::difference_type 
    operator+(const Iterator<T> &lhs, const Iterator<L> &rhs)
    {
            return (lhs.base() + rhs.base());
    }

    template<class T>
    inline typename Iterator<T>::difference_type 
    operator-(const Iterator<T> &lhs, const Iterator<T> &rhs)
    {
            return (lhs.base() - rhs.base());
    }

    template<class T, class L>
    inline typename Iterator<T>::difference_type 
    operator-(const Iterator<T> &lhs, const Iterator<L> &rhs)
    {
            return (lhs.base() - rhs.base());
    }

    template<class T>
    inline Iterator<T> operator+(int n, const Iterator<T> &rhs)
    {
        return Iterator<T>(rhs.base() + n);
    }

    template <typename IteratorType>
    class reverse_iterator
    {
    protected:
        IteratorType _current;

    public:
        typedef IteratorType                                            iterator_type;
        typedef typename iterator_traits<iterator_type>::value_type      value_type;
        typedef typename iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename iterator_traits<iterator_type>::reference       reference;
        typedef typename iterator_traits<iterator_type>::pointer         pointer;

        reverse_iterator(IteratorType it) : _current(it) {}

        iterator_type base() const
        {
            return _current;
        }

        // Dereverence Operator
        typename IteratorType::reference operator*() const
        {
            IteratorType temp = _current;
            return (*(--temp));
        }

        reverse_iterator &operator++()
        {
            --_current;
            return (*this);
        }
        reverse_iterator &operator++(int)
        {
            reverse_iterator temp = *this;
            --_current;
            return (*this);
        }
        reverse_iterator &operator--()
        {
            ++_current;
            return (*this);
        }
        reverse_iterator &operator--(int)
        {
            reverse_iterator temp = *this;
            ++_current;
            return (*this);
        }

        // Comparison operators
        bool operator==(const reverse_iterator &other) const
        {
            return _current == other._current;
        }
        bool operator!=(const reverse_iterator &other) const
        {
            return (_current != other._current);
        }

        //Find operator
        reverse_iterator operator+(difference_type n) const
        {
            return reverse_iterator(_current - n);
        }

        reverse_iterator& operator+=(difference_type n)
        {
            _current -= n;
            return *this;
        }

        reverse_iterator operator-(difference_type n) const
        {
            return reverse_iterator(_current + n);
        }

        reverse_iterator& operator-=(difference_type n)
        {
            _current += n;
            return *this;
        }
    };
}
#endif
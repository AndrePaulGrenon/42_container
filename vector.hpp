#ifndef VECTOR_H
#define VECTOR_H

#include <string>
#include <memory>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "utility.hpp"
#include "iterators.hpp"

namespace ft
{
    template <typename T, class Allocator = std::allocator<T> >
    class vector
    {
    public:
        // [ DEFINITIONS ]
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename ft::Iterator<T> iterator;
        typedef typename ft::Iterator<const T> const_iterator;
        typedef ft::reverse_iterator<iterator>           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

        //   [ CONSTRUCTORS ]
        explicit vector(const allocator_type &alloc = allocator_type()) : _m_allocator(alloc), _start(NULL), 
            _end(NULL), _size(0), _capacity(0) 
        {
            //std::cout << "EMPTY CONSTRUCTOR called ID : " << this << std::endl;
            return; 
        }
                                                                         
        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()) : 
                        _m_allocator(alloc),  _start(NULL), _end(NULL), _size(0), _capacity(0)
        {
            //std::cout << "DEFAULT CONSTRUCTOR called ID : " << this << std::endl;
            assign(n, val);
            return;
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), 
            typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type * = 0) : _m_allocator(alloc)
        {
            //std::cout << "ITERATOR CONSTRUCTOR called with ID : " << this << std::endl;
            size_t n = last - first;
            if (n <= 0)
                return ;
            _start = _m_allocator.allocate(n);
            _size = n;
            _capacity = n;
            for (size_t i = 0; i < n; i++)
                _m_allocator.construct(&_start[i], *(first++));
            _end = _start + n;
            return;
        }

        vector(const vector &x) : _m_allocator(x._m_allocator), _size(0), _capacity(0)
        {
            assign(x.begin(), x.end());
            return;
        }

        vector& operator=(const vector& other)
        {
            if (_start != NULL && capacity() > 0)
            {
                _m_allocator.deallocate(_start, capacity());
            }
            _start = NULL;
            _end = NULL;
            if (other.capacity() > 0)
            {
                    _start = _m_allocator.allocate(other.capacity());
                    ft::Iterator<const T> it = other.begin();
                    for (size_t i = 0; i < other.size(); i++)
                    {
                        _m_allocator.construct(&_start[i], *it++);
                    }
                    _end = _start + _size;
            }
            _capacity = other.capacity();
            _size = other.size();
            return *this;
        }

        ~vector()
        {
            if (_start != NULL && capacity() > 0)
            {
                for(size_type i = 0; i < size(); i++)
                    _m_allocator.destroy(_start + i);
                _m_allocator.deallocate(_start, capacity());
                _start = NULL;
            }
            return;
        }

        // [ VARIABLE ]

    private:
        allocator_type  _m_allocator;
        pointer         _start;
        pointer         _end;
        size_type       _size;
        size_type       _capacity;

    public:
        // [ELEMENT ACCESS MEMBER FUNCTIONS[]
        reference operator[](size_type n) 
        { 
            if (n > capacity() || n < 0)  
                throw std::out_of_range("Ridiculous ! The index is out of range");
            return (this->_start[n]); 
        }

        const_reference operator[](size_type n) const 
        { 
            if (n > capacity() || n < 0)  
                throw std::out_of_range("Ridiculous ! The index is out of range");
            return (this->_start[n]); 
        }

        reference at(size_type n)
        {
            if (n > _size || n < 0)
                throw std::out_of_range("Ridiculous ! The index is out of range");
            return (this->_start[n]);
        }
        const_reference at(size_type n) const
        {
            if (n > _size || n < 0)
                throw std::out_of_range("Ridiculous ! The index is out of range");
            return (this->_start[n]);
        }
        reference front(void) { return (this->_start[0]); }
        const_reference front(void) const { return (this->_start[0]); }
        reference back(void) { return (this->_start[this->size() - 1]); }
        const_reference back(void) const { return (this->_start[this->size() - 1]); }
        pointer data(void) { return (this->_start); }
        const_pointer data(void) const {return (this->_start);}

        // ITERATOR MEMBER FUNCTIONS
        iterator begin(void) { return iterator(_start); }
        iterator end(void) { return iterator(_end); }
        const_iterator begin(void) const { return const_iterator(_start); }
        const_iterator end(void) const { return const_iterator(_end); }
    
        reverse_iterator rbegin(void) { return reverse_iterator(this->end()); }
        reverse_iterator rend(void) { return reverse_iterator(this->begin()); }
        const_reverse_iterator rbegin(void) const { return const_reverse_iterator(this->end()); }
        const_reverse_iterator rend(void) const { return const_reverse_iterator(this->begin()); }

        // CAPACITY MEMBER FUNCTIONS
        bool empty(void) const
        {
            if (_size == 0)
                return (true);
            return (false);
        }
        size_type size(void) const { return (_size); }
        
        void resize(size_type n, value_type val = value_type())
        {
            if (n > _capacity)
            {                                                                
                size_t new_capacity = std::max(n, 2 * capacity());           
                T *new_data = _m_allocator.allocate(new_capacity);                  
                std::uninitialized_copy(_start, _start + size(), new_data);      
                std::uninitialized_fill(new_data + size(), new_data + n, val);
                if (_start != NULL && capacity() > 0)
                    _m_allocator.deallocate(_start, capacity());
                _start = new_data; 
                _end = _start + size();                                            
                _capacity = new_capacity;                                     
            }
            else if (n > size())
            {                                                        
                std::uninitialized_fill(_start + size(), _start + n, val); 
            }
            else if (n < size())
            {
                for (size_t i = 0; i < size() - n; i++)
                {
                    _m_allocator.destroy(_start + n);
                }
                _end = _start + n;
            }
            _size = n; 
        }

        size_type capacity(void) const { return (this->_capacity); }

        size_type max_size(void) const{return (_m_allocator.max_size());}

        void reserve(size_type n)
        {
           
            if (n > max_size())
                throw std::length_error("Ridiculous ! How can you even consider such a lenght?");
            if (n > capacity())
            {
                pointer temp = _m_allocator.allocate(n);
                for (size_t i = 0; i < _size; i++)
                {
                    _m_allocator.construct(&temp[i], _start[i]);
                }
                if (_start != NULL && capacity() > 0)
                   _m_allocator.deallocate(_start, capacity());
                _start = temp;
                _end = _start + size();
                _capacity = n;

            }
            return;
        }

        //INSERT FUNCTIONS

        iterator insert (iterator position, const value_type& val) 
        {
            size_type index = position - begin();
            if (size() + 1 > capacity()) {
                if (capacity() == 0)
                    reserve(1);
                else
                    reserve(capacity() * 2);
            }
            _size++;
            if (index < size()) {
                for (size_type i = size() - 1; i > index; i--) 
                {
                    _m_allocator.construct(&_start[i], _start[i - 1]);
                    _m_allocator.destroy(&_start[i - 1]);
                }
            }
            _m_allocator.construct(&_start[index], val);
            _end++;
            return iterator(&_start[index]);
        };

        void insert (iterator position, size_type n, const value_type& val) 
        {
            size_type index = position - begin();
            if (size() + n > capacity()) {
                if (capacity() == 0)
                    reserve(n);
                else 
                {
                    if (size() * 2 >= size() + n)
                        reserve(size() * 2);
                    else
                        reserve(size() + n);
                }
            }
            for (size_type i = n + size() - 1; i > index + n - 1; i--) {
                _m_allocator.construct(&_start[i], _start[i - n]);
                _m_allocator.destroy(&_start[i - n]);
            }
            for (size_type i = index; i < index + n; i++) {
                _m_allocator.construct(&_start[i], val);
                _size++;
            }
            _end = _start + size();
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) 
        {
           
            try
            {
                size_type offset = position - begin();
                InputIterator tmp = first;
                difference_type n = last - tmp;

                if (first >= last || position < begin() || position > end())
                    return ;
                //std::cout << " INSERT passes !" << std::endl;
                if (size() + n > capacity()) 
                {
                    //std::cout << "NEEDS to reserve " << std::endl;
                    if (capacity() == 0)
                        reserve(n);
                    else 
                    {
                        if (size() * 2 >= size() + n)
                            reserve(size() * 2);
                        else
                            reserve(size() + n);
                    }
                }
                for (size_type i = n + size() - 1; i > offset + n - 1; i--) 
                {
                    _m_allocator.construct(&_start[i], _start[i - n]);
                    _m_allocator.destroy(&_start[i - n]);
                }
                for (size_type i = offset; i < offset + n; i++) 
                {
                    _m_allocator.construct(&_start[i], *first);
                    first++;
                    _size++;
                }
                _end = _start + size();
            }
            catch(...)
            {
                if (_start != NULL && capacity() > 0)
                {
                    for(size_type i = 0; i < size(); i++)
                        _m_allocator.destroy(_start + i);
                        _m_allocator.deallocate(_start, capacity());
                        _start = NULL;
                }
                    _size = 0;
                    _capacity = 0;
                    _start = NULL;
                    _end = NULL;
                    throw std::bad_alloc();
            }
        };

        //SHRINK TO FIT FUNCTION
        void shrink_to_fit(void)
        {
            if (size() + 2 < capacity())
            {
                pointer temp = _m_allocator.allocate(this->size() + 1, _start);
                for (size_t i = 0; i < _size; i++)
                    _m_allocator.construct(&temp[i], _start[i]);
                _start = temp;
                _capacity = _size;
            }
        }

        //ERASE FUNCTIONS

        iterator erase (iterator position) 
        {
            if (position < begin() || position >= end()) 
                throw std::out_of_range("Invalid iterator passed to erase function");
            size_type pos = position - begin();
    
            _size--;
            _end--;
            if (pos < size()) 
            {
                _m_allocator.destroy(&_start[pos]);
                for (size_type i = pos; i < size(); i++) 
                {
                    _m_allocator.construct(&_start[i], _start[i + 1]);
                    _m_allocator.destroy(&_start[i + 1]);
                }
            }
            return iterator(&_start[pos]);
        };


        iterator erase (iterator first, iterator last)
        {
            
            if (_start == NULL || _end == NULL)
                return iterator(first);
            if (first >= last)
                return iterator(first);
            if (first < begin() || first > end() || last < begin() || last > end())
                return iterator (first);
            size_type pos_at = first - begin();
            size_type n = last - first;
            _m_allocator.destroy(_start + pos_at + n);
            for (size_type i = 0; i < size() - n; ++i) 
            {
                this->_m_allocator.construct(_start + pos_at + i, _start[pos_at + n + i]);
                this->_m_allocator.destroy(_start + pos_at + i + n);
            }
            _size = _size - n;
            _end = _start + size();
            return iterator(_start + pos_at);
        };

        // CLEAR MEMBER FUNCTIONS

        void clear(void)
        {
            if (size() > 0)
                erase(begin(), end());
        }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last, 
                typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
        {
            size_type        new_size = 0;
            InputIterator    tmp = first;

            if (first >= last)
            {
                _start = NULL;
                _end = NULL;
                _capacity = 0;
                _size = 0;
                return ;
            }
            for (size_type i = 0; i < _size; i++)
                _m_allocator.destroy(&(_start[i]));
            while (tmp++ != last)
                new_size++;
            if (new_size > capacity())
                reserve(new_size);
            for (size_type i = 0; i < new_size; i++)
                _m_allocator.construct(&(_start[i]), first[i]);
            if (new_size < _size)
            {
                for (size_t i = new_size; i < _size; i++)
                    this->_m_allocator.destroy(&(_start[i]));
            }
            _size = new_size;
        }

        void assign(size_type n, const value_type &val)
        {
            for (size_type i = 0; i < _size; i++)
                _m_allocator.destroy(&(_start[i]));
            if (n > capacity())
            {
                try
                {
                    reserve(n);
                }
                catch (const std::exception& e)
                {
                    if (_start != NULL && capacity() > 0)
                        _m_allocator.deallocate(_start, capacity());
                    _start = NULL;
                    _end = NULL;
                    _size = 0;
                    _capacity = 0;
                    throw std::out_of_range("vector");
                }
            }
            _size = n;
            for (size_t i = 0; i < size(); i++)
            {
                _m_allocator.construct(&_start[i], val);
            }
            _end = _start + n;
        }

        void push_back(const value_type &val)
        {
            if (this->size() + 1 >= this->capacity())
            {
                if (capacity() == 0)
                    this->reserve(1);
                else
                    this->reserve(this->capacity() * 2);
            }
            _size++;
            _m_allocator.construct(_end, val);
            _end++;
        }

        void pop_back(void)
        {
            if (!size())
                return ;
             _m_allocator.destroy(&_start[size() - 1]);
            _size--;
            _end = _start + size();
        }
        
        //ALLOCATOR MEMBER FUNCTION
        allocator_type  get_allocator(void) const { return (_m_allocator);}

        //SWAP MEMBER FUNCTION
       
        void swap (vector &x)
        {
            ft::swap(_m_allocator, x._m_allocator);
		    ft::swap(_size, x._size);
		    ft::swap(_capacity, x._capacity);
		    ft::swap(_start, x._start);
		    ft::swap(_end, x._end);
        }
    };

    //    [RELATIONAL OPERATORS]
    template <typename T, typename Alloc>
    inline bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename T, typename Alloc>
    inline bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T, typename Alloc>
    inline bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename T, typename Alloc>
    inline bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    template <typename T, typename Alloc>
    inline bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        return rhs < lhs;
    }

    template <typename T, typename Alloc>
    inline bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif
#ifndef STACK_H
#define STACK_H

#include <deque>
#include "vector.hpp"

namespace ft
{


    template <typename T, class Container = ft::vector<T> >
    class Stack {
    public:
        typedef Container                                container_type;
        typedef typename container_type::value_type      value_type;
        typedef typename container_type::size_type       size_type;
        typedef typename container_type::reference       reference;
        typedef typename container_type::const_reference const_reference;

        explicit Stack(const container_type& ctnr = container_type()) : _ctn(ctnr) {}

        Stack(const Stack& other) : _ctn(other._ctn) {}

        Stack& operator=(const Stack& other)
        {
            _ctn = other._ctn;
            return *this;
        }

        ~Stack(){}

        bool empty() const {
            return _ctn.empty();
        }

        std::size_t size() const {
            return _ctn.size();
        }

        T& top() {
            return _ctn.back();
        }

        const T& top() const {
            return _ctn.back();
        }

        void push(const T& value) {
            _ctn.push_back(value);
        }

        void pop() {
            _ctn.pop_back();
        }

        //FRIEND OVERLOAD OPERATOR

        template <typename T1, typename C1>
        friend bool operator==(const Stack<T1, C1>& lhs, const Stack<T1, C1>& rhs);

        template <typename T1, typename C1>
        friend bool operator<(const Stack<T1, C1>& lhs, const Stack<T1, C1>& rhs);

    protected:
        container_type  _ctn;
    };

    //RELATIONAL OPERATORS

    template <typename T, typename Con>
    inline bool operator==(const Stack<T, Con>& lhs, const Stack<T, Con>& rhs)
    {
        return lhs._ctn == rhs._ctn;
    }

    template <typename T, typename Con>
    inline bool operator!=(const Stack<T, Con>& lhs, const Stack<T, Con>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T, typename Con>
    inline bool operator<(const Stack<T, Con>& lhs, const Stack<T, Con>& rhs)
    {
        return lhs._ctn < rhs._ctn;
    }

    template <typename T, typename Con>
    inline bool operator<=(const Stack<T, Con>& lhs, const Stack<T, Con>& rhs)
    {
        return !(rhs < lhs);
    }

    template <typename T, typename Con>
    inline bool operator>(const Stack<T, Con>& lhs, const Stack<T, Con>& rhs)
    {
        return rhs < lhs;
    }

    template <typename T, typename Con>
    inline bool operator>=(const Stack<T, Con>& lhs, const Stack<T, Con>& rhs)
    {
        return !(lhs < rhs);
    }


}//close Namespace ft
#endif
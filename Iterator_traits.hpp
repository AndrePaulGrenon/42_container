#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "iterators.hpp"
#include <cstddef>

namespace ft
{

    template <typename T>
    struct IteratorTraits
    {
        // Define the types for the iterator's value, difference, pointer, and reference.
        typedef T value_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;

        // Specify the iterator category as std::random_access_iterator_tag.
        typedef std::random_access_iterator_tag iterator_category;
    };


    // template <typename Iter>
    // struct iterator_traits
    // {
    //     typedef typename Iter::difference_type difference_type;
    //     typedef typename Iter::value_type value_type;
    //     typedef typename Iter::pointer pointer;
    //     typedef typename Iter::reference reference;
    //     typedef typename Iter::iterator_category iterator_category;
    // };

    // template <class Iter>
    // struct iterator_traits<Iter *>
    // {
    //     typedef Iter value_type;
    //     typedef ptrdiff_t difference_type;
    //     typedef typename Iter::iteraetor_category iterator_category;
    //     typedef Iter *pointer;
    //     typedef Iter &reference;
    // };

    // template <class Iter>
    // struct iterator_traits<const Iter>
    // {
    //     typedef Iter value_type;
    //     typedef ptrdiff_t difference_type;
    //     typedef typename Iter::iterator_category iterator_category;
    //     typedef Iter *pointer;
    //     typedef Iter &reference;
    // };
}

#endif
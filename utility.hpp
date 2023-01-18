#ifndef UTILITY_H
#define UTILITY_H
    
#include "iterators.hpp"

    namespace ft
    {
        //PAIR STRUCT
        template<class T1, class T2>
        struct pair
        {
            typedef T1 first_type;
            typedef T2 second_type;

            pair(void): first(first_type()), second(second_type()) {return ;}
            pair(const pair &pr) : first(pr.first), second(pr.second){}
            pair(const first_type &a, const second_type &b) : first(a), second(b) {}
            pair &operator=(const pair &pr) {first = pr.first; second = pr.second; return *this;}

            first_type first;
            second_type second;
        };
        
        template <typename T1, typename T2>
        pair<T1, T2> make_pair(T1 x, T2 y)
        {
            return pair<T1, T2>(x, y);
        }

        template <typename T1, typename T2>
        inline bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }

        template <typename T1, typename T2>
        inline bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return !(lhs == rhs);
        }

        template <typename T1, typename T2>
        inline bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return (lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
        }

        template <typename T1, typename T2>
        inline bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return !(rhs < lhs);
        }

        template <typename T1, typename T2>
        inline bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return rhs < lhs;
        }

        template <typename T1, typename T2>
        inline bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
        {
            return !(lhs < rhs);
        }

        //SIMPLE ALGORITHMS
        template <class T>  
        void swap (T& a, T& b)
        {
            T c(a); a = b ; b = c ;
        }
        
        template <typename InputIt1, typename InputIt2>
        bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
        {
            for (InputIt1 first = first1; first != last1; ++first, ++first2) 
            {
                if (!(*first == *first2)) 
                    return false;
            }
            return true;
        }

        template <typename InputIt1, typename InputIt2>
        bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
        {
            for (; first2 != last2; ++first1, (void)++first2) {
                if (first1 == last1 || *first1 < *first2) {
                    return true;
                }
                if (*first2 < *first1) {
                    return false;
                }
            }
            return false;
        }

        template <typename InputIt1, typename InputIt2, typename Compare>
        bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
                                    Compare comp)
        {
            for (; first2 != last2; ++first1, (void)++first2) {
                if (first1 == last1 || comp(*first1, *first2)) {
                    return true;
                }
                if (comp(*first2, *first1)) {
                    return false;
                }
            }
            return false;
        }


        //METAPROGRAMMING 

                template<bool is_valid, typename T>
        struct valid_iterator_tag_res{ typedef T type; const static bool value = is_valid; };

        //DEFINE WHAT IS TRUE AND WHAT IS NOT
        //Custom template with default behavior
        template<typename T>
        struct is_input_iterator_tag : public valid_iterator_tag_res<false, T> {};

        //template specialisations:
        template<>
        struct is_input_iterator_tag<ft::input_iterator_tag > 
            : public valid_iterator_tag_res<true, ft::input_iterator_tag > {};

        template<>
        struct is_input_iterator_tag<ft::forward_iterator_tag>
            : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};

        template<>
        struct is_input_iterator_tag<ft::bidirectional_iterator_tag> 
            : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};

        template<>
        struct is_input_iterator_tag<ft::random_access_iterator_tag> 
            : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};


        //IMPLEMENTATION OF ENABLE_IF
        //FALSE
        template<bool B, typename T = void> struct enable_if {};
        //TRUE
        template<class T> struct enable_if<true, T> {typedef T type;};

        //IMPLEMENTATION OF IS_INTEGRAL
        //Default case
        template<class T>
        struct is_integral{ static const bool value = false; };

        //Specific cases
        template<>
        struct is_integral<bool> 
        { static const bool value = true;};
        template<>
        struct is_integral<char>{ static const bool value = true;};
        template<>
        struct is_integral<unsigned char>{ static const bool value = true;};
        template<>
        struct is_integral<char16_t>{ static const bool value = true;};
        template<>
        struct is_integral<char32_t>{ static const bool value = true;};
        template<>
        struct is_integral<wchar_t>{ static const bool value = true;};
        template<>
        struct is_integral<short>{ static const bool value = true;};
        template<>
        struct is_integral<unsigned short>{ static const bool value = true;};
        template<>
        struct is_integral<int>{ static const bool value = true;};
        template<>
        struct is_integral<unsigned int>{ static const bool value = true;};
        template<>
        struct is_integral<long>{ static const bool value = true;};
        template<>
        struct is_integral<unsigned long>{ static const bool value = true;};
        template<>
        struct is_integral<long long>{ static const bool value = true;};
        template<>
        struct is_integral<unsigned long long>{ static const bool value = true;};
        template<>
        struct is_integral<float>{ static const bool value = true;};


        template <typename T, T v>
        struct integral_constant {
            static const bool value = v;
            typedef T value_type;
            typedef integral_constant type;

            operator value_type() const
            {
                return value;
            }

            value_type operator()() const
            {
                return value;
            }
        };

        template <bool V>
        struct bool_constant : public integral_constant<bool, V> {
        };

        struct true_type : public bool_constant<true> {
        };

        struct false_type : public bool_constant<false> {
        };

        template <typename T, typename U>
        struct is_same : public false_type {
        };

        template <typename T>
        struct is_same<T, T> : public true_type {
        };

    }
#endif
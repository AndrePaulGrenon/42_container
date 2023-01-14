#ifndef UTILITY_H
#define UTILITY_H
    
    namespace ft
    {
        //SIMPLE ALGO SWAP
        template <class T>  
        void swap (T& a, T& b)
        {
            T c(a); a = b ; b = c ;
        }
        
        //ALGORYTHMS USING ITERATORS
        template<typename InputIt1, typename InputIt2>
        bool equal (InputIt1 first1, InputIt1 last1, InputIt2 first2)
        {
            for (InputIt1 it = first1; it != last1; it++, first2++)
            {
                if ((*first1 != *first2))
                    return false;
            }
            return (true);
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
    }
#endif
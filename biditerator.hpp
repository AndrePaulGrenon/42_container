#ifndef BID_ITERATOR_H
#define BID_ITERATOR_H

#pragma once

#include "iterators.hpp"
#include <iterator>
#include "Map.hpp"
#include "utility.hpp"


namespace ft
{
    template <class node>
    struct bidirectional_iterator 
    {
        typedef std::size_t                         size_type;
        typedef typename ft::pair<typename node::key_type, typename node::mapped_type> pair;

        typedef node                                iterator_type;
        typedef ft::iterator_traits<iterator_type>  traits;
        typedef typename traits::value_type         value_type;
        typedef typename traits::difference_type    difference_type;
        typedef typename traits::pointer            pointer;
        typedef typename traits::reference          reference;
        typedef typename std::bidirectional_iterator_tag iterator_category;

        bidirectional_iterator(pointer ptr = pointer()) : _m_ptr(ptr) { }
       
        bidirectional_iterator(const bidirectional_iterator &iter) : _m_ptr(iter._m_ptr), _sent(iter._sent) {}
       
       //bidirectional_iterator Assignment operator
        bidirectional_iterator& operator=(const bidirectional_iterator &iter) { _m_ptr = iter._m_ptr; return *this;}

        ~bidirectional_iterator() {}

        pointer base(void) const { return this->_m_ptr; }

        pair operator*(void) { return (_m_ptr->_data); }
        pointer operator->() const { return (_m_ptr); }

        // Input bidirectional_iterator Incrementation
        bidirectional_iterator &operator++(void)
        {
            if (_m_ptr == NULL)
                return (*this);
            _m_ptr = ft_next_node(_m_ptr);
            return (*this);
        }
        bidirectional_iterator &operator--(void)
        {
            if (_m_ptr == NULL)
                return (*this);
            _m_ptr = ft_previous_node(_m_ptr);
            return (*this);
        }

        bidirectional_iterator operator++(int)
        {
            bidirectional_iterator temp(*this);
            _m_ptr = ft_next_node(_m_ptr);
            return temp;
        }
        bidirectional_iterator operator--(int)
        {
            bidirectional_iterator temp(*this);
            _m_ptr = ft_previous_node(_m_ptr);
            return temp;
        }
   
    protected:
        node *_m_ptr;
        node *_sent;

    private: 

        node *ft_next_node(node *current)
        {
            _sent = NULL;
            // std::cout << " THIS ROOT IS " << (*current->root)->_data.first << std::endl;
            if (current->right == NULL)
                current = ft_find_next(*current->root, current);
            else
            {
                current = current->right;
                while (current->left)
                    current = current->left;
            }
            // std::cout << " THIS ROOT IS " << (*current->root)->_data.first << std::endl;
            return (current);
        }

        node    *ft_find_next(node *root, node *target)
        {
            node *temp = NULL;
            
            _sent = root;
            if (root == NULL || target == NULL)
                return NULL;
            if (target->_data.first > root->_data.first)
            {
                _sent = root;
                temp = ft_find_next(root->right, target);
                if (temp == NULL && root->_data.first > target->_data.first)
                    return root;
                _sent = root;
                return temp;
            }
            if (target->_data.first < root->_data.first)
            {
                _sent = root;
                temp = ft_find_next(root->left, target);
                if (temp == NULL && root->_data.first > target->_data.first)
                    return root;
                _sent = root;
                return temp;
            }
            return temp;
        }
        
        node *ft_previous_node(node *current)
        {
            _sent = NULL;
            if (current->left == NULL)
                current = ft_find_previous(*current->root, current);
            else
            {
                current = current->left;
                while (current->right)
                    current = current->right;
            }
            return (current);
        }

        node    *ft_find_previous(node *root, node *target)
        {
            node *temp = NULL;
            
            _sent = root;
            if (root == NULL || target == NULL)
                return NULL;
            if (target->_data.first > root->_data.first)
            {
                _sent = root;
                temp = ft_find_previous(root->right, target);
                if (temp == NULL && root->_data.first < target->_data.first)
                    return root;
                _sent = root;
                return temp;
            }
            if (target->_data.first < root->_data.first)
            {
                _sent = root;
                temp = ft_find_previous(root->left, target);
                if (temp == NULL && root->_data.first < target->_data.first)
                    return root;
                _sent = root;
                return temp;
            }
            return temp;
        }


    };

    template<class T>
    inline bool operator==(const ft::bidirectional_iterator<T> &lhs, const ft::bidirectional_iterator<T> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }

    template<class T, class L>
    inline bool operator==(const ft::bidirectional_iterator<T> &lhs, const ft::bidirectional_iterator<L> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }
    
    template<class T>
    inline bool operator!=(const ft::bidirectional_iterator<T> &lhs, const ft::bidirectional_iterator<T> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

    template<class T, class L>
    inline bool operator!=(const ft::bidirectional_iterator<T> &lhs, const ft::bidirectional_iterator<L> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

}
#endif
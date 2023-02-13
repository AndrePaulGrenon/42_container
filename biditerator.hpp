#ifndef BID_ITERATOR_H
#define BID_ITERATOR_H

#pragma once

#include "iterators.hpp"
#include <iterator>
#include "Map.hpp"
#include "utility.hpp"
#include <memory>


namespace ft
{
    template <class node>
    struct bidirectional_iterator 
    {
        typedef std::size_t                         size_type;
        typedef typename ft::pair<const typename node::key_type, typename node::mapped_type> pair;

        typedef node                                iterator_type;
        typedef iterator_type*                      pointer_type;
        typedef ft::iterator_traits<iterator_type>  traits;
        typedef typename    iterator_type::value_type   value_type;
        typedef value_type*                 pointer;
        typedef value_type&                 reference;
        typedef typename traits::difference_type    difference_type;
        typedef typename std::bidirectional_iterator_tag iterator_category;

        bidirectional_iterator(iterator_type *ptr = pointer_type()) : _m_ptr(ptr) { }
       
        bidirectional_iterator(const bidirectional_iterator &iter) : _m_ptr(iter._m_ptr), _sent(iter._sent) {}
       
       //bidirectional_iterator Assignment operator
        bidirectional_iterator& operator=(const bidirectional_iterator &iter) { _m_ptr = iter._m_ptr; return *this;}

        ~bidirectional_iterator() {}

        pointer_type base(void) const { return (_m_ptr); }

        reference operator*(void) const { return (_m_ptr->_data);}

        // const_reference operator*(void) const {return (_m_ptr->_data);}

        pointer operator->() { return (&(_m_ptr->_data)); }
        
        // const_pointer operator->() const { return (&(_m_ptr->_data)); }

        // Input bidirectional_iterator Incrementation
        bidirectional_iterator &operator++(void)
        {
            if (_m_ptr == NULL || (*_m_ptr->root) == NULL)
                return (*this);
            node *temp = _m_ptr->the_end;
            _m_ptr = ft_next_node(_m_ptr);
            if (_m_ptr ==  NULL)
                _m_ptr = temp;
            return (*this);
        }
        bidirectional_iterator &operator--(void)
        {
            if (_m_ptr == NULL || (*_m_ptr->root) == NULL)
                return (*this);
            if (_m_ptr->_endNode == true)
            {
                node *temp = *_m_ptr->root;
                while (temp->right)
                    temp = temp->right;
                _m_ptr = temp;
                return (*this);
            }
            node *temp = _m_ptr;
            _m_ptr = ft_previous_node(_m_ptr);
            if (_m_ptr == NULL)
                _m_ptr = temp;
            return (*this);
        }

        bidirectional_iterator operator++(int)
        {
            if (_m_ptr == NULL || (*_m_ptr->root) == NULL)
                return (*this);
            bidirectional_iterator temp(*this);
            node *temp2 = _m_ptr->the_end;
            _m_ptr = ft_next_node(_m_ptr);
            if (_m_ptr == NULL)
                _m_ptr = temp2;
            return temp;
        }

        bidirectional_iterator operator--(int)
        {
            if (_m_ptr == NULL || (*_m_ptr->root) == NULL)
                return (*this);
            bidirectional_iterator temp(*this);
            if (_m_ptr->_endNode)
            {
                node *temp = *_m_ptr->root;
                while (temp->right)
                    temp = temp->right;
                _m_ptr = temp;
                return (temp);
            }
            _m_ptr = ft_previous_node(_m_ptr);
            return (temp);
        }
   
    public:
        node *_m_ptr;
        node *_sent;

    private: 

        node *ft_next_node(node *current)
        {
            _sent = NULL;
            
            if (current->right == NULL)
            {
                if (current == (*current->root))
                {
                    return NULL;
                }
                current = ft_find_next(*current->root, current);
            }
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



    //CONST BIDIRECTIONAL OPERATOR

    template <class node>
    struct const_bidirectional_iterator
    {

        typedef std::size_t                         size_type;
        typedef typename ft::pair<const typename node::key_type, typename node::mapped_type> pair;

        typedef node                                iterator_type;
        typedef iterator_type*                      pointer_type;

        
        typedef ft::iterator_traits<iterator_type>  traits;
        typedef typename    iterator_type::value_type   value_type;
        typedef const value_type *          pointer;
        typedef const value_type &          reference;
        // typedef typename traits::value_type         value_type;
        typedef typename traits::difference_type    difference_type;
        // typedef typename traits::pointer            pointer;
        // typedef typename traits::reference          reference;
        typedef typename std::bidirectional_iterator_tag iterator_category;

        const_bidirectional_iterator(iterator_type *ptr = pointer_type()) : _m_ptr(ptr) { }
       
        const_bidirectional_iterator(const const_bidirectional_iterator &iter) : _m_ptr(iter._m_ptr), _sent(iter._sent) {}
       
       //const_bidirectional_iterator Assignment operator
        const_bidirectional_iterator& operator=(const const_bidirectional_iterator &iter) { _m_ptr = iter._m_ptr; return *this;}

        ~const_bidirectional_iterator() {}

        const pointer_type base(void) const { return (_m_ptr); }

        // value_type operator*(void) { return (_m_ptr->_data);}
        reference operator*(void) const { return (_m_ptr->_data);}
        // reference operator*(void) const { return (const_cast<pair &>(_m_ptr->_data));}

        // value_type *operator->() { return (&(_m_ptr->_data)); }
        // pointer operator->() const{ return (&(_m_ptr->_data)); }
        pointer operator->() const{ return (&(operator*())); }
        // pointer operator->() const{ return (const_cast<pair *>(&(_m_ptr->_data))); }

        // Input const_bidirectional_iterator Incrementation
        const_bidirectional_iterator &operator++(void)
        {
            if (_m_ptr == NULL || (*_m_ptr->root) == NULL)
                return (*this);
            node *temp = _m_ptr->the_end;
            _m_ptr = ft_next_node(_m_ptr);
            if (_m_ptr ==  NULL)
                _m_ptr = temp;
            return (*this);
        }
        const_bidirectional_iterator &operator--(void)
        {
            if (_m_ptr == NULL || (*_m_ptr->root) == NULL)
                return (*this);
            if (_m_ptr->_endNode == true)
            {
                node *temp = *_m_ptr->root;
                while (temp->right)
                    temp = temp->right;
                _m_ptr = temp;
                return (*this);
            }
            node *temp = _m_ptr;
            _m_ptr = ft_previous_node(_m_ptr);
            if (_m_ptr == NULL)
                _m_ptr = temp;
            return (*this);
        }

        const_bidirectional_iterator operator++(int)
        {
            if (_m_ptr == NULL || (*_m_ptr->root) == NULL)
                return (*this);
            const_bidirectional_iterator temp(*this);
            node *temp2 = _m_ptr->the_end;
            _m_ptr = ft_next_node(_m_ptr);
            if (_m_ptr == NULL)
                _m_ptr = temp2;
            return temp;
        }

        const_bidirectional_iterator operator--(int)
        {
            if (_m_ptr == NULL || (*_m_ptr->root) == NULL)
                return (*this);
            const_bidirectional_iterator temp(*this);
            if (_m_ptr->_endNode)
            {
                node *temp = *_m_ptr->root;
                while (temp->right)
                    temp = temp->right;
                _m_ptr = temp;
                return (temp);
            }
            _m_ptr = ft_previous_node(_m_ptr);
            return (temp);
        }
   
    public:
        node *_m_ptr;
        node *_sent;

    private: 

        node *ft_next_node(node *current)
        {
            _sent = NULL;
            
            if (current->right == NULL)
            {
                if (current == (*current->root))
                {
                    return NULL;
                }
                current = ft_find_next(*current->root, current);
            }
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
    inline bool operator==(const ft::const_bidirectional_iterator<T> &lhs, const ft::bidirectional_iterator<T> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }

    template<class T, class L>
    inline bool operator==(const ft::const_bidirectional_iterator<T> &lhs, const ft::bidirectional_iterator<L> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }
    
    template<class T>
    inline bool operator!=(const ft::const_bidirectional_iterator<T> &lhs, const ft::bidirectional_iterator<T> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

    template<class T, class L>
    inline bool operator!=(const ft::const_bidirectional_iterator<T> &lhs, const ft::bidirectional_iterator<L> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

    template<class T>
    inline bool operator==(const ft::bidirectional_iterator<T> &lhs, const ft::const_bidirectional_iterator<T> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }

    template<class T, class L>
    inline bool operator==(const ft::bidirectional_iterator<T> &lhs, const ft::const_bidirectional_iterator<L> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }
    
    template<class T>
    inline bool operator!=(const ft::bidirectional_iterator<T> &lhs, const ft::const_bidirectional_iterator<T> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

    template<class T, class L>
    inline bool operator!=(const ft::bidirectional_iterator<T> &lhs, const ft::const_bidirectional_iterator<L> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

    //ONLY CONST_BIDIRECTIONAL
    template<class T>
    inline bool operator==(const ft::const_bidirectional_iterator<T> &lhs, const ft::const_bidirectional_iterator<T> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }

    template<class T, class L>
    inline bool operator==(const ft::const_bidirectional_iterator<T> &lhs, const ft::const_bidirectional_iterator<L> &rhs) 
    {
        return (lhs.base() == rhs.base());
    }
    
    template<class T>
    inline bool operator!=(const ft::const_bidirectional_iterator<T> &lhs, const ft::const_bidirectional_iterator<T> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }

    template<class T, class L>
    inline bool operator!=(const ft::const_bidirectional_iterator<T> &lhs, const ft::const_bidirectional_iterator<L> &rhs) 
    {
        return (lhs.base() != rhs.base());
    }


}
#endif
#ifndef MAP_H
#define MAP_H

#pragma once

#include <functional>
#include "biditerator.hpp"
#include "utility.hpp"
#include "iterators.hpp"
#include "tree_algo.hpp"
#include "colours.hpp"
#include "redblack_algo.hpp"

namespace ft
{

    //------------------------------------------------------------------------------
    //   |------------|
    //   |NODE STRUCT |
    //   |------------|
    //------------------------------------------------------------------------------

    template <class Key, class T>
    struct node
    {
        typedef Key key_type;
        typedef T   mapped_type;

        node() : _data(ft::pair<const Key, T>()), left(NULL), right(NULL), _isRed(true) {}
        node(ft::pair<const Key, T> data) : _data(data), left(NULL), right(NULL), _isRed(true) {}
        node(ft::pair<const Key, T> data, bool isRed) : _data(data), left(NULL), right(NULL) , _isRed(isRed){}
        node    &operator=(const node &no) {_data = no._data; left = no.left; right = no.right;
            _isRed = no._isRed;}
        ~node() {}
        ft::pair<const Key, T> _data;
        node *left;
        node *right;
        node **root;
        bool _isRed;
    };

    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<node<const Key, T> > >
    class Map
    {

        //------------------------------------------------------------------------------
        //   |------------|
        //   |DEFINITIONS |
        //   |------------|
        //------------------------------------------------------------------------------

    public:

        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        typedef ft::pair<const key_type, mapped_type>                   value_type;
        typedef Compare                                                 key_compare;
        typedef Allocator                                               allocator_type;
        typedef ptrdiff_t                                               difference_type;
        typedef size_t                                                  size_type;
        typedef node<const key_type, mapped_type>                             node;

        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;

        typedef typename ft::bidirectional_iterator<node>               iterator;
        typedef typename ft::bidirectional_iterator<const node>         const_iterator;
        typedef typename ft::reverse_iterator<iterator>                 reverse_iterator; 
        typedef typename ft::reverse_iterator<const_iterator>           const_reverse_iterator;
        
        // ------------------------------------------------------------------------------
        //   |------------|
        //   |ValueCOMPARE|
        //   |------------|
        // ------------------------------------------------------------------------------

        class value_compare
        {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
            friend class map;
            protected:
            key_compare comp;
            value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
            public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };

        // ------------------------------------------------------------------------------
        //   |------------|
        //   |CONSTRUCTORS|
        //   |------------|
        // ------------------------------------------------------------------------------

        explicit Map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
            _root(NULL), comp(comp), _m_alloc(alloc) , _size(0)
        {

        }

        template <class InputIterator>  
        Map (InputIterator first, InputIterator last,
            const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
            _root(NULL), comp(comp), _m_alloc(alloc), _size(0)
        {
            for (; first != last; first++)
            {
                insert(*first);
                _size++;
            }
        }

        Map(const Map &x) : _root(NULL), comp(x.comp), _m_alloc(x._m_alloc), _size(0)
        {
            iterator begin = x.begin();
            iterator end = x.end();

            for (; begin != end; begin++)
            {
                insert(*begin);
            }
        }

        //   |---------|
        //   |Destuctor|
        //   |---------|

        ~Map()
        {
            while (_root != NULL)
            {
                erase(_root->_data.first);
            }
        }

        //   |-----------|
        //   |ASSIGNEMENT|
        //   |-----------|

        Map& operator=(const Map& other)
        {
            while (_root != NULL)
                erase(_root->_data.first);
            insert(other.begin(), other.end());
        }

        //------------------------------------------------------------------------------
        //   |-----------|
        //   |MEMBER VARS|
        //   |-----------|
        //------------------------------------------------------------------------------

            node            *_root;
        protected:
            key_compare     comp;
            allocator_type  _m_alloc;
            size_type       _size;

            //SENTINELLES Insert
            node            *_papa_sent;
            node            *_daddy_sent;
            node            *_child_sent;
            node            *_new_insert;
           
            bool            simul_over;
            bool            double_black;

        public:

        //------------------------------------------------------------------------------
        //   |-------------------|
        //   |ITERATORS FUNCTIONS|
        //   |-------------------|
        //------------------------------------------------------------------------------

        iterator    begin(void)
        {
            if (_root == NULL)
                return end();
            node *temp = _root;
            while (temp->left)
                temp = temp->left;
            return iterator (temp);
        }

        iterator    end(void)
        {
            return iterator(NULL);
        }
        

        //------------------------------------------------------------------------------
        //   |-------------------|
        //   |MODIFIERS FUNCTIONS|
        //   |-------------------|
        //------------------------------------------------------------------------------

        //            a. INSERT 

        ft::pair<iterator, bool> insert(const value_type& val) 
        {
            sent_null();
            simul_over = false;
            if (_root == NULL)
            {
                _root = create(val, false);
                return ft::pair<iterator, bool>(iterator(_root),true) ;
            }
            ft::pair<iterator, bool> answer = check_node(_root, val);
            _root = RB_tree_balancing(_root);
            _size++;
            return (answer);
        }

        iterator    insert (iterator position, const value_type& val)
        {
            sent_null();
            simul_over = false;
            if (_root == NULL)
            {
                _root = create(val, false);
                return iterator(_root);
            }
            if ((position.base()->_isRed))
                insert(val);

            ft::pair<iterator, bool> answer = check_node(position.base(), val);
            _root = RB_tree_balancing(_root);
            _size++;
            if (position->left->_data.first == val.first)
                return iterator(position->left);
            return iterator (position->right);
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last) 
        {
            for (; first != last; first++)
            {
                insert(*first);
            }
            return ;
        }

        //          b. ERASE FUNCTIONS 

        void erase (iterator position)
        {
            erase((*position).first);
        }

        size_type   erase (const key_type& k)
        {
            sent_null();
            // bool isRed = _root->_isRed;
            // std::cout << BRED "KEY is : [" << k << "]" CLEAR << std::endl;
            size_type val = deletes(_root, k);
            // delete_RB_balancing(_root, isRed);
            // Put AVL balancing function instead; 
            // _root = AVL_tree_balancing(_root); 
            return (val);
        }

        void erase (iterator first, iterator last)
        {
            iterator temp(first);
            for (; first != last; first++)
            {
                if (first.base() == NULL)
                    break;   
                erase((*temp).first);
                temp = first;
            }
        }

        //      c. CLEAR FUNCTION

        void clear()
        {
            while (_root != NULL)
            {
                erase(_root->_data.first);
            }
        }


        //------------------------------------------------------------------------------
        //   |-------------------|
        //   |LOOK UP   FUNCTIONS|
        //   |-------------------|
        //------------------------------------------------------------------------------

        //      a. COUNT FUNCTION
        size_type   count( const key_type& key ) const
        {
            node    *temp = ft_find(_root, key);

            if (temp != NULL)
                return (1);
            return (0);
        }

        //      b. FIND FUNCTION

        node    *ft_find(node *current , const key_type& key) const 
        {
            if (current == NULL)
                return NULL;
            if (current->_data.first == key)
                return current;
            if (comp(current->_data.first, key))
                return (ft_find(current->right, key));
            if (!comp(current->_data.first, key))
                return (ft_find(current->left, key));
            return (NULL);
        }

        iterator    find(const Key& key)
        {
            return iterator(ft_find(_root, key));
        }

        const_iterator find (const key_type& key) const
        {
            return const_iterator(ft_find(_root, key));
        }

        iterator lower_bound( const Key& key )
        {
            (void) key;
        }

        //----------------------------------------------------------
        //   |-----------------|
        //   |UTILITY FUNCTIONS|
        //   |-----------------|
        // ----------------------------------------------------------

    private: 

        node    *create(const value_type &data, bool isRed) 
        {
            std::cout << "   --Inserted key :" << data.first << " with val : " << data.second << std::endl;
            
            // node *newnode = new node(data, isRed);
            node *newnode = _m_alloc.allocate(1);
            _m_alloc.construct(newnode, data, isRed);
            // newnode->_isRed = isRed;
            if (_root == NULL)
                newnode->root = &newnode;
            else
                newnode->root = &_root;
            _papa_sent = newnode;
            return newnode;
        }
        
        //  | AVL BALANCING TREE|
        // Defines the rules used to rebalance the subtree according to AVL tree.
        // Is applied on all nodes of the path and returns Root of the subtree that is being rebalance. 
        // node    *AVL_tree_balancing(node *nod)
        // {
        //     int   difference;
            
        //     if (nod != NULL)
        //     {
        //         difference = ft::treeHeight(nod->left) - ft::treeHeight(nod->right);
        //         if (difference > 1)
        //         {
        //             int childDif = ft::treeHeight(nod->left->left) - ft::treeHeight(nod->left->right);

        //             std::cout << GRN "Right Rotation : " CLEAR << childDif << std::endl;
        //             if (childDif > 0)
        //             {
        //                 std::cout <<MAG "Single" CLEAR << std::endl;
        //                 return (ft::RightRotation(nod));
        //             }
        //             std::cout << RED "Double" CLEAR<< std::endl;
        //             nod->left = LeftRotation(nod->left);
        //             return (ft::RightRotation(nod));
        //         }
        //         if (difference < -1) 
        //         {
        //             int childDif = ft::treeHeight(nod->right->left) - ft::treeHeight(nod->right->right);
        //             std::cout << BLU "LEFT Rotation : " CLEAR << childDif << std::endl;
        //             if (childDif < 0)
        //             {
        //                 std::cout << MAG "Single" CLEAR<< std::endl;
        //                 return (ft::LeftRotation(nod));
        //             }
        //             std::cout <<RED "Double" CLEAR<< std::endl;
        //             nod->right = RightRotation(nod->right);
        //             return (LeftRotation(nod));
        //         }
        //     }
        //     return (nod);
        // }

        //  | RED BLACK BALANCING TREE|
        // Defines the rules used to rebalance the subtree according to Red Black tree.
        // Is applied on all nodes of the path and returns Root of the subtree that is being rebalance. 
       
        node    *RB_tree_balancing(node *nod)
        {
            if (nod != _papa_sent || simul_over)
                return (nod);
            if (nod == NULL )
                return (nod);
            if (_child_sent && _child_sent->_isRed && _daddy_sent->_isRed 
                && (_new_insert == NULL || _new_insert == _child_sent)) // Checks one out of 2 times
            {
                std::cout <<RED " Grandather :  " << _papa_sent->_data.first << MAG " Daddy is :" 
                << _daddy_sent->_data.first << YEL " Child is : " << _child_sent->_data.first 
                << CLEAR << std::endl;
                if (ft_uncle_isRed(nod, _daddy_sent))
                {
                    nod->left->_isRed = false;
                    nod->right->_isRed = false;
                    if (_papa_sent != _root)
                        _papa_sent->_isRed = true;
                    _new_insert = _papa_sent;
                }
                else 
                {
                    _new_insert = _papa_sent;
                    node *temp = ft_choose_rotation(_papa_sent, _daddy_sent, _child_sent);
                    ft_switch_colour(temp);
                    return temp;
                }
            }
            _child_sent = _daddy_sent;
            _daddy_sent = _papa_sent;
            return (nod);
        }

        //RECURSIVELY CHECK AND INSERTS NEW NODE
        ft::pair<iterator, bool>    check_node(node *nod, const value_type &val)
        {
            ft::pair<iterator, bool>    answer;

            //check is key is same
            if (val.first == nod->_data.first)
                return ft::pair<iterator, bool>(iterator(nod), false);
            //check if Key is bigger --  with less<key> default behavior is: if (val.first > nod->_data.first) 
            if (!comp(val.first, nod->_data.first))
            {
                //Creates node or goes down the right path
                if (nod->right == NULL)
                {
                    std::cout << std::endl << "FATHER key :" << nod->_data.first << std::endl << " RIGHT: "<< "  - ";
                    nod->right = create(val, true);
                    nod->left = RB_tree_balancing(nod->left); // not sure if useful IN AVL 
                    nod->right = RB_tree_balancing(nod->right); // not sure if useful IN AVL
                    _papa_sent = nod;
                    if (nod->_isRed == false || nod == _root)  // Used in RB tree
                        simul_over = true;
                    return ft::pair<iterator, bool>(iterator(nod->right), true);
                }
                answer = check_node(nod->right, val);
                nod->left = RB_tree_balancing(nod->left);
                nod->right = RB_tree_balancing(nod->right);
                _papa_sent = nod;
                return (answer);
            }
            
            //If key is smaller --- woth less<key> default behavior is : if (val.first < nod->_data.first)
            if (comp(val.first, nod->_data.first))
            {
                //Creates node or goes down the left path
                if (nod->left == NULL)
                {
                    std::cout << std::endl << "Father key :" << nod->_data.first << std::endl << " LEFT: ";
                    nod->left = create(val, true);
                    nod->left = RB_tree_balancing(nod->left); // not sure if useful IN AVL
                    nod->right = RB_tree_balancing(nod->right); // not sure if useful IN AVL
                    _papa_sent = nod;
                    if (nod->_isRed == false || _root == nod) // Used in RB tree
                        simul_over = true;
                    return ft::pair<iterator, bool>(iterator(nod->right), true);
                }
                answer = check_node(nod->left, val);
                nod->left = RB_tree_balancing(nod->left);
                nod->right = RB_tree_balancing(nod->right);
                _papa_sent = nod;
                return (answer);
            }
            std::cout << "  node : "<< nod->_data.first << RED " Balance Height : " CLEAR << ft::treeHeight(nod->left) << "  - "; 
            return ft::pair<iterator, bool>(iterator(nod), false);
        }

        //|----------------------------|
        //| DELETION IN REDBLACK TREE  |
        //|----------------------------|

            //DELETION operation for a node with one Edge. Returns the child node. 
        template <class node>
        node    *ft_one_edge(node *toDelete)
        {
            node    *temp;
            
            if (toDelete->right == NULL)
                temp = toDelete->left;
            else
                temp = toDelete->right;
            delete toDelete;
            return (temp);
        }

            //DELETION operation for a 2 edges node. Will replace this node with the..
    // ..next highest value of its left tree 
        node    *ft_two_edges(node *toSwap)
        {
            node    *temp = toSwap->left;
            node    *temp2;

            // std::cout << "Two Edge " << std::endl;
            _papa_sent = toSwap;
            _daddy_sent = temp;
            _child_sent = temp->right;
            //IF the left node has no right node
            if (temp->right == NULL)
            {
                // std::cout << "Simple Route" << std::endl;
                temp->right = toSwap->right;           
                _child_sent = temp->left;
                //  std::cout << " _daddy is : " << _daddy_sent->_data.first << std::endl;
                _papa_sent = ft_find_parent(_root, _daddy_sent);
                // if (_papa_sent != NULL)
                // std::cout << " Find is  : " << _papa_sent->_data.first << std::endl;
                // std::cout << " SEGFAULT  : "  << std::endl;
                if (temp->_isRed == false)
                    double_black = true;
                delete toSwap;
                return temp;
            }

            //IF the left node has some right nodes
            while (temp->right->right)
            {
                // std::cout << "Extra Hard Route" << std::endl;
                _papa_sent = temp;
                _daddy_sent = temp->right;
                _child_sent = temp->right->right;
                temp = temp->right;
            }
                //             std::cout << BBLU ;
                // std::cout << _papa_sent->_data.first << " [GRANDPA] :  " << std::endl;
                // std::cout << _daddy_sent->_data.first << " [DADDY] :  " << std::endl;
                // if (_child_sent != NULL)
                //     std::cout << _child_sent->_data.first << " [CHILD] :  " << std::endl;
                // else
                //     std::cout << "[CHILD] is NULL " << std::endl;
                // std::cout << CLEAR ;
            if (_papa_sent == toSwap)
                _papa_sent = temp->right;
            if (_daddy_sent == toSwap)
                _daddy_sent = temp->right;
            _child_sent = temp->right->left;

            temp2 = temp->right;
            temp->right = temp->right->left;
            temp2->right = toSwap->right;
            temp2->left = toSwap->left;
            if (temp2->_isRed == false)
                double_black = true;
            delete toSwap;
            return temp2;
        }

        void    delete_RB_balancing(node *new_value, bool isRed)
        {
            //  std::cout << BGRN "DELETE RB BALANCING " CLEAR << std::endl;
            if (new_value == NULL && isRed)
                return ;
            if (_child_sent == _root)
            {
                if (_root != NULL)
                    _root->_isRed = false;
                return ;
            }
            bool currentVal;
            if (new_value != NULL)
            {
                currentVal = new_value->_isRed;
                new_value->_isRed = isRed;
            }
            if (double_black)
            {
                double_black_case();
                return ;
            }
            //makes sure the tree is red 
            if (ft_n_edges(new_value) == 1 && new_value->_isRed)
                ft_switch_colour(new_value);
            return ;
        }

        //UTILITY function , looks for the parent node of the target
        node    *ft_find_parent(node *root, node *target)
        {
            // std::cout << " target is : " << target->_data.first << std::endl;
            if (root == NULL || target == NULL)
                return NULL;
            if (_root == target)
                return (_root);
            if (root == target)
                return root;
            if (root->left == target)
                return root;
            if (root->right == target)
                return root;
            if (root->left != NULL && !comp(root->_data.first, target->_data.first))
                return ft_find_parent(root->left, target);
            if (root->right != NULL && comp(root->_data.first, target->_data.first))
                return ft_find_parent(root->right, target);
            return NULL;
        }

        //Uses _daddy_sent as the node to check 
        void    double_black_case(void)
        {
            double_black = false;

            //PRINT SENTINELLES : 
            // if (_papa_sent != NULL)
            // std::cout << _papa_sent->_data.first << " [GRANDPA] :  " << std::endl;
            // if (_daddy_sent != NULL)
            // std::cout << _daddy_sent->_data.first << " [DADDY] :  " << std::endl;
            // if (_child_sent != NULL)
            // std::cout << _child_sent->_data.first << " [CHILD] :  " << std::endl;
            // else
            //     std::cout << "[CHILD] is NULL " << std::endl;

            //case 1 :  is Root
            if (_child_sent == _root)
            {
                // std::cout << BHRED "Case 1 entered " CLEAR << std::endl;
                _child_sent->_isRed = false;
                return ;
            }

            //case 2: sibling is red with 2 black childs
            if (ft_brother_isRed(_daddy_sent, _child_sent) && ft_sibling_has_black_children(_daddy_sent, _child_sent))
            {
                // std::cout << BHRED "Case 2 entered " CLEAR << std::endl;
                if (_daddy_sent == _root && _daddy_sent->right == _child_sent)
                {
                    _root = RightRotation(_daddy_sent);
                    _papa_sent = _root;
                    _daddy_sent = _root->right;
                    _papa_sent->_isRed =  false;
                    _papa_sent->right->_isRed = true;
                }
                else if (_daddy_sent == _root && _daddy_sent->left == _child_sent)
                {
                    _root = LeftRotation(_daddy_sent);
                    _papa_sent = _root;
                    _daddy_sent = _root->left;
                    _papa_sent->_isRed =  false;
                    _papa_sent->left->_isRed = true;
                }
                else if (_daddy_sent->left == _child_sent && _papa_sent->right == _daddy_sent)
                {
                    _papa_sent->right = LeftRotation(_daddy_sent);
                    _papa_sent->right->_isRed = false;
                    _papa_sent->right->left->_isRed = true;
                    _daddy_sent = _papa_sent->right->left;
                    _papa_sent = _papa_sent->right;
                }
                else if (_daddy_sent->left == _child_sent && _papa_sent->left == _daddy_sent)
                {
                    _papa_sent->left = LeftRotation(_daddy_sent);
                    _papa_sent->left->_isRed = false;
                    _papa_sent->left->left->_isRed = true;
                    _daddy_sent = _papa_sent->left->left;
                    _papa_sent = _papa_sent->left;
                }
                else if (_daddy_sent->right == _child_sent && _papa_sent->left == _daddy_sent)
                {
                    _papa_sent->left = RightRotation(_daddy_sent);
                    _papa_sent->left->_isRed = false;
                    _papa_sent->left->right->_isRed = true;
                    _daddy_sent = _papa_sent->left->right;
                    _papa_sent = _papa_sent->left;
                }
                else if (_daddy_sent->right == _child_sent && _papa_sent->right == _daddy_sent)
                {                    
                    _papa_sent->right = RightRotation(_daddy_sent);
                    _papa_sent->right->_isRed = false;
                    _papa_sent->right->right->_isRed = true;
                    _daddy_sent = _papa_sent->right->right;
                    _papa_sent = _papa_sent->right;
                }
            }

            //case 3: brother is not Red and has two black child
            if (!ft_brother_isRed(_daddy_sent, _child_sent) && ft_sibling_has_black_children(_daddy_sent,_child_sent)
                && !_daddy_sent->_isRed)
            {
                // std::cout << BHBLU "Case 3 entered " CLEAR << std::endl;
                if (_daddy_sent->right != _child_sent && _daddy_sent->right != NULL)
                    _daddy_sent->right->_isRed = true;
                if (_daddy_sent->left != _child_sent && _daddy_sent->left != NULL)
                     _daddy_sent->left->_isRed = true;

                //Push the problem up
                _child_sent = _daddy_sent;
                _daddy_sent = _papa_sent;
                _papa_sent = ft_find_parent(_root, _papa_sent);
                double_black_case();
                return ;
            }

            //case 4
            if (_daddy_sent->_isRed && !ft_brother_isRed(_daddy_sent, _child_sent) &&
                    ft_sibling_has_black_children(_daddy_sent, _child_sent))
            {
                // std::cout << BHCYN "CASE 4" CLEAR << std::endl;
                _daddy_sent->_isRed = false;
                if (_daddy_sent->left != NULL && _daddy_sent->left != _child_sent)
                    _daddy_sent->left->_isRed= true;
                if (_daddy_sent->right != NULL && _daddy_sent->right != _child_sent)
                    _daddy_sent->right->_isRed = true;
                return ;
            }

            //case 5.a
            if (_daddy_sent->right != _child_sent && !ft_brother_isRed(_daddy_sent, _child_sent)
                    && (_daddy_sent->right->left != NULL && _daddy_sent->right->left->_isRed)
                    && (_daddy_sent->right->right == NULL || _daddy_sent->right->right->_isRed == false))
            {
                // std::cout << BHMAG "Cas 5.a" CLEAR << std::endl;
                _daddy_sent->right = RightRotation(_daddy_sent->right);
                _daddy_sent->right->_isRed = false;
                _daddy_sent->right->right->_isRed = true;
            }

            //case 5.b
            else if (_daddy_sent->left != _child_sent && !ft_brother_isRed(_daddy_sent, _child_sent)
                    && (_daddy_sent->left->right != NULL && _daddy_sent->left->right->_isRed)
                    && (_daddy_sent->left->left == NULL || _daddy_sent->left->left->_isRed == false))
            {
                // std::cout << BHMAG "Cas 5.b" CLEAR << std::endl;
                _daddy_sent->left = LeftRotation(_daddy_sent->left);
                _daddy_sent->left->_isRed = false;
                _daddy_sent->left->left->_isRed = true;
            }
            
            //case 6 a. Left Rotation
            if (_daddy_sent->right != _child_sent)
            {
                // std::cout << BHCYN "Cas 6 a" CLEAR << std::endl;
                if (_daddy_sent == _root)
                {
                    _root = LeftRotation(_daddy_sent);
                    _root->_isRed = false;
                    _root->left->_isRed = false;
                    _root->right->_isRed = false;
                    return ;
                }
                else if (_papa_sent->left == _daddy_sent)
                {
                    _papa_sent->left = LeftRotation(_daddy_sent);
                    _papa_sent->left->_isRed = _daddy_sent->_isRed;
                     if (_papa_sent->left->right != NULL)
                        _papa_sent->left->right->_isRed = false;
                }
                else if (_papa_sent->right)
                {
                    _papa_sent->right = LeftRotation(_daddy_sent);
                    _papa_sent->right->_isRed = _daddy_sent->_isRed;
                     if (_papa_sent->right->right != NULL)
                        _papa_sent->right->right->_isRed = false;
                }
                _daddy_sent->_isRed = false;
                return ;
            }

            //case 6 b. Right Rotation (mirror)
            if (_daddy_sent->left != _child_sent)
            {
                // std::cout << BHCYN "Cas 6 b" CLEAR << std::endl;
                if (_daddy_sent == _root)
                {
                    _root = RightRotation(_daddy_sent);
                    _root->_isRed = false;
                    _root->left->_isRed = false;
                    _root->right->_isRed = false;
                    return ;
                }
                else if (_papa_sent->left == _daddy_sent)
                {
                    _papa_sent->left = RightRotation(_daddy_sent);
                    _papa_sent->left->_isRed = _daddy_sent->_isRed;
                    if (_papa_sent->left->left != NULL)
                        _papa_sent->left->left->_isRed = false;
                }
                else if (_papa_sent->right)
                {
                    _papa_sent->right = RightRotation(_daddy_sent);
                    _papa_sent->right->_isRed = _daddy_sent->_isRed;
                    if (_papa_sent->right->left != NULL)
                        _papa_sent->right->left->_isRed = false;
                }
                _daddy_sent->_isRed = false;
            }
            return ;
        }

        //recursively deletes nodes
        size_type    deletes(node *nod, const key_type &key)
        {
            _papa_sent = _daddy_sent;
            if (_papa_sent == NULL)
                _papa_sent = _root;
            _daddy_sent = nod;

            // std::cout << _papa_sent->_data.first << " [GRANDPA] :  " << std::endl;
            // std::cout << _daddy_sent->_data.first << " [DADDY] :  " << std::endl;
            // if (_child_sent != NULL)
            //     std::cout << _child_sent->_data.first << " [CHILD] :  " << std::endl;
            // else
            //     std::cout << "[CHILD] is NULL " << std::endl;

            if (_root == NULL)
                return(0) ;
            if (key != nod->_data.first && nod->left == NULL && nod->right == NULL)
                return(0) ;
            
            //check is left node the ONE
            if (nod->left && key == nod->left->_data.first)
            {
                // std::cout << nod->left->_data.first << " [DELETED] :  ";
                bool isRed = nod->left->_isRed;
                if (!ft_n_edges(nod->left))
                {
                    if (!nod->left->_isRed)
                        double_black = true;
                    delete nod->left;
                    nod->left = NULL;
                    _child_sent =  NULL;
                }
                else if (ft_n_edges(nod->left) == 1)
                    nod->left = ft_one_edge(nod->left);
                else if (ft_n_edges(nod->left) == 2)
                    nod->left = ft_two_edges(nod->left);
                delete_RB_balancing(nod->left, isRed);//Checks and ajusts with RB tree rules
                
                return (1);
            }
           
            //CHECK if right node is the ONE
            if (nod->right && key == nod->right->_data.first)
            {
                //Select 0 , 1 or 2 edges case
                // std::cout << nod->right->_data.first << " [DELETED] :  ";
                bool isRed = nod->right->_isRed;
                if (!ft_n_edges(nod->right))
                {
                    // std::cout << "     -No edge Deletion case" << std::endl;
                    // is double black 
                    if (!nod->right->_isRed)
                        double_black = true;
                    delete nod->right;
                    nod->right = NULL;
                    _child_sent =  NULL;
                }
                else if (ft_n_edges(nod->right) == 1)
                    nod->right = ft_one_edge(nod->right);
                else if (ft_n_edges(nod->right) == 2)
                    nod->right = ft_two_edges(nod->right);
                delete_RB_balancing(nod->right, isRed); //Checks and ajusts with RB tree rules
                return (1);
            }
            //IF Node is ROOT
            if (key == nod->_data.first)
            {
                // std::cout << nod->_data.first << " [DELETED] : /ROOT  " ;
                bool isRed = nod->_isRed;
                if (!ft_n_edges(nod))
                {
                    delete nod;
                    _root = NULL;
                }
                else if (ft_n_edges(nod) == 1)
                    _root = ft_one_edge(nod);
                else if (ft_n_edges(nod) == 2)
                    _root = ft_two_edges(nod);
                // _child_sent = _root;
                delete_RB_balancing(_root, isRed); //Checks and ajusts with RB tree rules
                return (1) ;
            }

            //check if Key is bigger and goes down the right path 
            if (!comp(key, nod->_data.first) && nod->right != NULL)
            {
                size_type val = deletes(nod->right, key);
                if (ft_n_edges(nod) == 1 && nod->_isRed)
                    ft_switch_colour(nod);
                return val ;
            }
            //If key is smaller and goes down the left path
            if (comp(key, nod->_data.first) && nod->left != NULL)
            {
                size_type val = deletes(nod->left, key);
                if (ft_n_edges(nod) == 1 && nod->_isRed)
                    ft_switch_colour(nod);
                return val ;
            }
            return (0);
        }


        //|----------------------------|
        //| DELETION IN AVL TREE       |
        //|----------------------------|
        // Uses the rebalancing function of the AVL. 

        // size_type    deletes(node *nod, const key_type &key)
        // {
        //     if (_root == NULL)
        //         return(0) ;
        //     if (key != nod->_data.first && nod->left == NULL && nod->right == NULL)
        //         return(0) ;
        //     //check is left node the ONE
        //     if (nod->left && key == nod->left->_data.first)
        //     {
        //         std::cout << nod->left->_data.first << " [DELETED] :  ";
        //         if (!ft_n_edges(nod->left))
        //         {
        //             std::cout << "     -No edge Deletion case" << std::endl;
        //             delete nod->left;
        //             nod->left = NULL;
        //         }
        //         else if (ft_n_edges(nod->left) == 1)
        //             nod->left = ft_one_edge(nod->left);
        //         else if (ft_n_edges(nod->left) == 2)
        //             nod->left = ft_two_edges(nod->left);
        //         nod->left = RB_tree_balancing(nod->left);
        //         return (1);
        //     }
           
        //     //CHECK if right node is the ONE
        //     if (nod->right && key == nod->right->_data.first)
        //     {
        //         //Select 0 , 1 or 2 edges case
        //         std::cout << nod->right->_data.first << " [DELETED] :  ";
        //         if (!ft_n_edges(nod->right))
        //         {
        //             std::cout << "     -No edge Deletion case" << std::endl;
        //             delete nod->right;
        //             nod->right = NULL;
        //         }
        //         else if (ft_n_edges(nod->right) == 1)
        //             nod->right = ft_one_edge(nod->right);
        //         else if (ft_n_edges(nod->right) == 2)
        //             nod->right = ft_two_edges(nod->right);
        //         nod->right = RB_tree_balancing(nod->right);
        //         return (1);
        //     }
        //     //IF Node is ROOT
        //     if (key == nod->_data.first)
        //     {
        //         std::cout << nod->_data.first << " [DELETED] : /ROOT  " ;
        //         if (!ft_n_edges(nod))
        //         {
        //             std::cout << "      -No edge Deletion" << std::endl;
        //             delete nod;
        //             _root = NULL;
        //         }
        //         else if (ft_n_edges(nod) == 1)
        //             _root = ft_one_edge(nod);
        //         else if (ft_n_edges(nod) == 2)
        //             _root = ft_two_edges(nod);
        //         _root = RB_tree_balancing(_root);
        //         return (1) ;
        //     }

        //     //check if Key is bigger and goes down the right path 
        //     if (!comp(key, nod->_data.first) && nod->right != NULL)
        //     {
        //         size_type val = deletes(nod->right, key);
        //         nod->right = RB_tree_balancing(nod->right);
        //         return val ;
        //     }
        //     //If key is smaller and goes down the left path
        //     if (comp(key, nod->_data.first) && nod->left != NULL)
        //     {
        //         size_type val = deletes(nod->left, key);
        //         nod->left = RB_tree_balancing(nod->left);
        //         return val ;
        //     }
        //     return (0);
        // }
        
        void    sent_null(void)
        {
            _child_sent = NULL;
            _daddy_sent = NULL;
            _papa_sent = NULL;
            _new_insert = NULL;
        }
    };

    template <typename Key, typename T, typename Compare, typename Allocator>
    inline void swap(Map<Key, T, Compare, Allocator>& x, Map<Key, T, Compare, Allocator>& y)
    {
        x.swap(y);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    inline bool operator==( const Map<Key,T,Compare, Alloc>& lhs, 
                            const Map<Key, T,Compare, Alloc>& rhs)
    {
        return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    inline bool operator!=( const Map<Key,T,Compare, Alloc>& lhs, 
                            const Map<Key, T,Compare, Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    inline bool operator<(  const Map<Key, T, Compare, Alloc>& lhs,
                            const Map<Key, T, Compare, Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    inline bool operator<=( const Map<Key,T,Compare, Alloc>& lhs, 
                            const Map<Key, T,Compare, Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    inline bool operator>(  const Map<Key, T, Compare, Alloc>& lhs, 
                            const Map<Key, T, Compare, Alloc>& rhs)
    {
        return rhs < lhs;
    }

    template <typename Key, typename T, typename Compare, typename Alloc>
    inline bool operator>=( const Map<Key, T, Compare, Alloc>& lhs,
                            const Map<Key, T, Compare, Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif
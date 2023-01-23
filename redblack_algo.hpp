#ifdef RED_BLACK_ALGO_H
#define RED_BLACK_ALGO_H

#include "map.hpp"

namespace ft
{


    template <class node>
    void    ft_child_colour_check(node *redParent)
    {
        
        if (redParent->_isred)
        {
            if (redParent->left != NULL)
                redParent->left->_isRed = false;
            if (redParent->right != NULL)
                redParent->right->_isRed = false;
        }
        return;
    }

}
#endif
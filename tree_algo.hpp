#ifndef TREE_ALGO_H
#define TREE_ALGO_H

#include "colours.hpp"

namespace ft
{

    //Checks if uncle node has two black child and returns true
    template <class node>
    bool    ft_sibling_has_black_children(node *grandPa, node *self)
    {
        node *daddy; 
        
        if (grandPa->left != self)
            daddy = grandPa->left;
        else
            daddy = grandPa->right;
        if ((daddy->left == NULL || !daddy->left->_isRed) 
                && (daddy->right == NULL || !daddy->right->_isRed))
            return true;
        return false;
    }

    //Checks for the correct rotation to take in the context of an insertion
    //Used by Red Black Tree;
    template<class node>
    node    *ft_choose_rotation(node *grandPa, node *daddy, node *child)
    {
        if (grandPa->left == daddy && daddy->right == child)
        {
            grandPa->left = LeftRotation(daddy);
            return (RightRotation(grandPa));
        }
        if (grandPa->left == daddy && daddy->left == child)
            return (RightRotation(grandPa));
        if (grandPa->right == daddy && daddy->left == child)
        {
            grandPa->right = RightRotation(daddy);
            return (LeftRotation(grandPa));
        }
        if (grandPa->right == daddy && daddy->right == child)
            return (LeftRotation(grandPa));
        return (NULL);
    }

    //Checks if node daddy has a sibbling and it is red, returns true
    // otherwise returns false. Used by red black tree
    template <class node>
    bool    ft_uncle_isRed(node *grandPa, node *daddy)
    {
        if (grandPa->left != NULL && grandPa->left != daddy)
            return grandPa->left->_isRed;
        if (grandPa->right != NULL && grandPa->right != daddy)
            return grandPa->right->_isRed;
        return false;
    }

    //checks if brother of child is red, returns true
    template <class node>
    bool    ft_brother_isRed(node *daddy, node *child)
    {
        if (daddy->right == NULL && daddy->left == NULL)
            return false;
        if (daddy->right != child && daddy->right != NULL)
            return (daddy->right->_isRed);
        if (daddy->left != child && daddy->left != NULL)
            return (daddy->left->_isRed);
        return false;
    }

    template <class node>
    void    ft_switch_colour(node *redParent)
    {
        if (redParent == NULL)
            return ;
        if (redParent->_isRed)
        {
            redParent->_isRed = false;
            if (redParent->left != NULL)
                redParent->left->_isRed = true;
            if (redParent->right != NULL)
                redParent->right->_isRed = true;
        }
        return;
    }

    //Recursively calculates the height of a tree
    //Used by Avl tree; 
    template <class node>
    int  treeHeight(node *nod)
    {
        if (nod == nullptr)
        {
            return (0);
        }
        int  leftHeight = treeHeight(nod->left) + 1;
        int  rightHeight = treeHeight(nod->right) + 1;
        return (std::max(leftHeight, rightHeight));
    }

    //ROTATION OPERATIONS
    //Left Left Rotation - Right Rotation
    template<class node>
    node    *RightRotation(node *nod)
    {
        node temp;

        temp.left = nod->left;
        
        nod->left = temp.left->right;
        temp.left->right = nod;
        return temp.left;
    }

    //Right rigtht Rotation - Left Rotation
    template<class node>
    node    *LeftRotation(node *nod)
    {
        node temp;

        temp.right = nod->right;
        
        nod->right = temp.right->left;
        temp.right->left = nod;
        return temp.right;
    }

    //CALCULATES the number of edges of a node
    template<class node>
    int ft_n_edges(const node *nod)
    {
        if (nod->right != NULL && nod->left != NULL)
            return (2);
        if (nod->right == NULL && nod->left != NULL)
            return (1);
        if (nod->right != NULL && nod->left == NULL)
            return (1);
        return 0;
    }

}

#endif
#ifndef PRINT_TREE_H
#define PRINT_TREE_H

#include <iostream>
namespace ft
{
    
    template <class node>
    int height(node* root) 
    {
        if (root == NULL) 
        {
            return 0;
        }
        else 
        {
            int leftHeight = height(root->left);
            int rightHeight = height(root->right);
            return std::max(leftHeight, rightHeight) + 1;
        }
    }

    void printIndentation(int level) 
    {
        for (int i = 0; i < level; i++) 
            std::cout << "  ";
        return ;
    }

    template <class node>
    void printTree(node* root, int level, bool isLeft) 
    {
        
        if (root == NULL) 
        {
            return;
        }
        if (level == 1) 
        {
            std::cout << root->_data.first << (root->_isRed ? BRED "R" CLEAR : BBLK "B" CLEAR );
            std::cout << (isLeft ? "/ " : "\\ ");

        }
        else if (level > 1) 
        {
            printTree(root->left, level-1, true);
            printTree(root->right, level-1, false);
        }
    }

    template <class node> 
    void printLevelOrder(node* root) 
    {
        std::cout << std::endl;
        int h = height(root);
        for (int i = 1; i <= h; i++) 
        {
            printIndentation(((h * 3) / 2) - i);
            printTree(root, i, true);
            std::cout << std::endl;
        }
    }

}
#endif
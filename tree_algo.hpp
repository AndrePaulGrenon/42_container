#ifndef TREE_ALGO_H
#define TREE_ALGO_H

namespace ft
{
    //Recursively calculates the height of a tree
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

    //DELETION operation for a node with one Edge. Returns the child node. 
    template <class node>
    node    *ft_one_edge(node *toDelete)
    {
        node    *temp;
            
        std::cout << "     -One edge Deletion case" << std::endl;
        if (toDelete->right == NULL)
            temp = toDelete->left;
        else
            temp = toDelete->right;
        delete toDelete;
        return (temp);
    }

    //DELETION operation for a 2 edges node. Will replace this node with the..
    // ..next highest value of its left tree
    template <class node>
    node    *ft_two_edges(node *toSwap)
    {
        node    *temp = toSwap->left;
        node    *temp2;
            
        std::cout << "      -Two edge Deletion case" << std::endl;
        //IF the left node has no right node
        if (temp->right == NULL)
        {
            std::cout << "    easy remove" << std::endl;
            temp->right = toSwap->right;
            delete toSwap;
            return temp;
        }
         std::cout << "    harder remove" << std::endl;
        //IF the left node has some right nodes
        while (temp->right->right)
            temp = temp->right;
        temp2 = temp->right;
        temp->right = temp->right->left;
        temp2->right = toSwap->right;
        temp2->left = toSwap->left;
        delete toSwap;
        return temp2;
    }
}

#endif
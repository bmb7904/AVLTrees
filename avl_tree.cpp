/**
 * Implementation file for AvlTree derived class. An AVL tree is a Binary Search Tree
 * that automatically balances itself with each new addition. All siblings within an
 * AVL tree have a height within 1 of each other. This is a derived class, from the
 * base template class BST<>
 *
 * @author Brett Bernardi
 * @date November 10, 2020
 */
#include "avl_tree.h"
#include <iostream>
#include <cmath>

/**
 * Returns true if node pointed at by Node<>* pointer parameter is unbalanced. False
 * otherwise. A node is balanced if the heights of its two children are within 1.
 * n Node<E>* a node pointer
 * bool true if unbalanced, false otherwise
 */
template <typename S>
bool AvlTree<S>::unbalanced(Node<S>* n)
{
    int left, right;
    left = (n->left == NULL)? -1:n->left->height;
    right = (n->right == NULL)? -1:n->right->height;
    return abs( (left) - (right) ) > 1;
}

/**
 * Returns a pointer to the node that contains the key specified in parameter. If data
 * is not in tree, returns NULL:
 *
 * T data
 * Node<>* node pointer to node containing data
 */
template <typename S>
Node<S>* AvlTree<S>::search_tree(S data)
{
    Node<S> *p = this->root;
    while(p!=NULL)
    {
        if(p->data == data)
        {
            return p;
        }

        if(data < p->data)
        {
            p = p->left;
        }
        else
            {
            p=p->right;
        }
    }
    return NULL;
}
/**
 * Restructures the three nodes passed as arguments. There are 4 possible cases
 * depending upon how the data of nodes x, y, z keys are related. After restructuring,
 * update heights of all nodes so when the subtree is added back to AVL tree, all
 * nodes' heights are updated and correct.
 *
 * Node<>* z - closest unbalanced ancestor of added node
 * Node<>* x - successor
 * Node<>* y - successor
*          Z                 Y
*         / \              /   \
*        Y   a            X     Z
*       / \       ==>    / \   / \
*      X   b            c   d b   a
*     / \
*    c   d

*
*     Z                Y
*    / \             /   \
*   a   Y    ==>    Z     X
*      / \         / \   / \
*     b   X       a   b c   d
*        / \
*       c   d

*       Z                     X
*      / \                  /   \
*     Y   a                Y     Z
*    / \          ==>     / \   / \
*   b   X                b   c d   a
*      / \
*     c   d

*       Z                     X
*      / \                  /   \
*     a   y                Z     Y
*        / \      ==>     / \   / \
*       X   b            a   c d   b
*      / \
*     c   d
*/
template <typename S>
Node<S>* AvlTree<S>::trinode_restructure(Node<S> *x, Node<S> *y, Node<S> *z)
{
    Node<S> *temp1, *temp2;
    // 4 different cases

    if(x->data < y->data)
    {

        if(y->data < z->data)
        {
            temp1 = y->right;
            y->right = z;
            z->parent = y;
            z->left = temp1;
            if(temp1!=NULL)
            {
                temp1->parent = z;
            }
            updateTriNodeHeights(x);
            updateTriNodeHeights(y);
            updateTriNodeHeights(z);
            return y;
        }

        else
        {
            temp1 = x->left;
            temp2 = x->right;

            x->left = z;
            x->right = y;
            y->parent = x;
            z->parent = x;
            z->right = temp1;

            y->left = temp2;
            if(temp1 != NULL)
            {
                temp1->parent = z;
            }
            if(temp2 != NULL)
            {
                temp2->parent = y;
            }
            updateTriNodeHeights(x);
            updateTriNodeHeights(y);
            updateTriNodeHeights(z);
            return x;

        }
    }
    else
    {
        if(y->data > z->data)
        {
            temp1 = y->left;
            y->left = z;
            z->parent = y;
            z->right = temp1;
            if(temp1!=NULL)
            {
                temp1->parent = z;
            }
            updateTriNodeHeights(x);
            updateTriNodeHeights(y);
            updateTriNodeHeights(z);
            return y;
        }
        else
        {
            temp1 = x->left;
            temp2 = x->right;

            x->left = y;
            x->right = z;
            y->parent = x;
            z->parent = x;
            y->right = temp1;
            z->left = temp2;
            if(temp1 != NULL)
            {
                temp1->parent = y;
            }
            if(temp2 != NULL)
            {
                temp2->parent = z;
            }
            updateTriNodeHeights(x);
            updateTriNodeHeights(y);
            updateTriNodeHeights(z);
            return x;
        }
    }
}
/**
 * Overriden virtual insert() function from the Base BST<> class. Will insert a new
 * peice of data into tree like an ordinary BST, but then balance the tree. Duplicates
 * are not allowed.
 * @param data
 */
template <typename S>
void AvlTree<S>::insert(S data)
{
    Node<S>  *parent, *newSubTreeRoot; // pointers used in restructuring

    // insert data into Tree like a normal BST using the base class insert()
    BST<S>::insert(data);

    // now, search for the node just added, and get a pointer to it
    Node<S> *temp = search_tree(data);

    Node<S>* z, *y, *x;

    // After newly inserted node is found, check ancestors for unbalanced nodes,
    // according to the rules of AVL trees.
    while(temp != NULL)
    {
        if (unbalanced(temp))
        {
            // At this point, we are at the nearest unbalanced ancestor of newly added
            // node(z). Find x and y.
            parent = temp->parent;
            z = temp;
            y = this->trinode_successor(z, z->data);
            x = this->trinode_successor(y, y->data);

            // set pointer to newly restructured subtree
            newSubTreeRoot = this->trinode_restructure(x,y,z);

            // if z's parent node is the root at top of tree
            if(parent==NULL)
            {
                this->root = newSubTreeRoot;
                this->root->parent = NULL;
            }
            else
            {
                // place new sub root into proper place on Z's parent node
                if(parent->right == z)
                {
                    parent->right = newSubTreeRoot;
                }
                else
                {
                    parent->left = newSubTreeRoot;

                }
                // set parent of new sub-tree node
                newSubTreeRoot->parent = parent;
            }
            // update heights of all ancestors of newly added node, as these are the
            // only nodes with heights liable to change.
            this->updateHeight(newSubTreeRoot);
            temp = newSubTreeRoot; // set temp

        }
        // increment temp to parent
        temp = temp->parent;
    }
}
/**
 * Takes an unbalanced node and finds its trinode successors. The node with the largest
 * height will be a successor.
 * @param n
 * @param d - not used
 * @return
 */
template <typename S>
Node<S>* AvlTree<S>::trinode_successor(Node<S>* n, S d)
{
    return (this->height(n->left) > this->height(n->right))? n->left:n->right;
}

/**
 * Updates heights of a node in a specific circumstance: when the node was just moved
 * in a trinode restructuring. Because all sub-trees of X,Y,Z in a trinode
 * restructuring are unchanged, this can only be used in this circumstance.
 *
 * Node<>* n - Either X, Y, Z node after a trinode restructuring.
 */
template <typename S>
void AvlTree<S>::updateTriNodeHeights(Node<S> *n)
{
    int left, right;
    if(n->left==NULL)
    {
        left = -1;
    }
    if(n->right==NULL)
    {
        right = -1;
    }
    n->height = 1 + std::max(left, right);
}
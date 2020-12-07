/**
 * Implementation of a Binary Search Tree. Template class. Has functions to insert
 * data, keep track of size, print out data in sorted order, etc.
 *
 * @author Brett Bernardi
 * @date November 10, 2020
 */
#include "bst.h"
#include <iostream>
#include <stdlib.h>

/**
 * Outputs keys of the tree via recursive inorder traversal. Called
 * from stream insertion operator.
 */
template <typename S>
void print(std::ostream& out, Node<S>* node)
{
    static int counter = 1;
    if(node==NULL)
    {
        return;
    }
    print(out, node->left);
    out << node->data << "  ";
    print(out, node->right);
}

/**
 * Overloaded stream operator that serves as a wrapper function to the in-order print()
 * function for printing out a BST.
 */
template <typename S>
std::ostream& operator<<(std::ostream& out, const BST<S>& tree)
{
    print(out, tree.root);
    return out;
}

/**
 * Iterative implementation of the insert function for a BST. No duplicates allowed.
 * So, if key already exists in Tree, no new node will be added. Height of each node is
 * updated with each new insertion. Also keeps sets left, right, and parent pointers of
 * each node.
 *
 * E data = data to be inserted into tree
 */
template <typename E>
void BST<E>::insert(E data)
{
    // allocate memory for a new node to be created
    Node<E> *newNode = new Node<E>(data);

    // if BST is empty
    if(root == NULL)
    {
        root = newNode;
        root ->left = NULL;
        root ->right = NULL;
        root ->parent = NULL;
        root ->height = 0;
        size++;
        return;
    }

    // if BST is not empty
    Node<E> *leading = root;
    Node<E> *preceding = leading;

    while (leading != NULL)
    {
        // if node with key already exits in tree, release memory associated with new node
        // and return. This is not added
        if(newNode->data == leading->data)
        {
            delete newNode;
            return;
        }
        if (newNode->data <= leading->data)
        {
            preceding = leading;
            leading = leading->left;

            if (leading == NULL)
            {
                preceding->left = newNode;
                newNode->parent = preceding;
                newNode->left = NULL;
                newNode->right = NULL;
                break;
            }
        }
        else {
            preceding = leading;
            leading = leading->right;

            if (leading == NULL)
            {
                preceding->right = newNode;
                newNode->parent = preceding;
                newNode->left = NULL;
                newNode->right = NULL;
                break;
            }
        }
    }
    size++; // increment size
    // update all heights of appropriate nodes including the one just inserted and all
    // its ancestors
    updateHeight(newNode);
}
/**
 * Function that will return the height of the node that the Node<>* parameter is pointing
 * at. The height of a node is defined as the number of edges between the node and the
 * farthest leaf. By definition, the height of a node with no children(leaf) is 0, and the
 * height of a non-existent node is -1. A node's height is related to the height of
 * its children. In fact, the height of node pointed at my Node<>* pointer n can be
 * determined from the following recursive relationship:
 *          height(n) = 1 + max(height(n->left), height(n->right));
 *
 * This is only called in the main.cpp program for calculating the height of the root
 * node.
 *
 * Node<>* n - Pointer to a node
 * Returns int -the height of the node
 */
template <typename E>
int BST<E>::height(Node<E>* n)
{
    // if Node doesn't exist, then pointer == NULL and , by convention, has a height of -1
    // this is the base case
    if(n == NULL)
    {
        return -1;
    }

    // get the height of left child and right child, find max, add 1, and return
    return 1 + std::max(height(n->left), height(n->right));
}
/**
 *  Recursively releases memory from tree. To release entire tree, pass root node into
 *  function parameter. This is used in the destructor.
 *
 *  Node<>* node - node pointer
 */

template <typename E>
void BST<E>::remove(Node<E>* node)
{
    if(node == NULL)
    {
        return;
    }
    remove(node->left);
    remove(node->right);
    delete node;
}
/**
 * Updates height of node specified in parameter, and then updates all ancestor nodes
 * of it until the root of the tree. With each new addition of a node, the only heights
 * that are affected by the new node will be ancestors of the new node.
 * Node<>* node - node pointer of recently added node.
 */
template <typename E>
void BST<E>::updateHeight(Node<E>* node)
{
    int left, right;

    // update height of node
    while(node!=NULL)
    {
        if(node->left==NULL)
        {
            left = -1;
        }
        else
        {
            left = node->left->height;
        }
        if(node->right == NULL)
        {
            right = -1;
        }
        else
        {
            right = node->right->height;
        }
        node->height = 1 + std::max(left, right);
        node = node->parent;
    }
}
/*
 * An AVL tree. Deletions are not supported.
 *
 * Author: Drue Coles and modified by Brett Bernardi
 */
 
#include "bst.cpp"

template <typename T>
class AvlTree : public BST<T> {

public:
    void insert(T data);
     
private:
    Node<T>* trinode_successor(Node<T>*, T);
    Node<T>* trinode_restructure(Node<T>*, Node<T>*, Node<T>*);
    bool unbalanced(Node<T>*);

    // These functions were added by Brett Bernardi
    Node<T>* search_tree(T data);
    void updateTriNodeHeights(Node<T> *n);
};
/*
 * Binary Search Tree. Deletions are not supported. Height field of Node struct is not
 * used, and height() function is called directly to calculate height of a node is
 * needed.
 *
 * Duplicates not used.
 *
 * Author: Modified by Brett Bernardi
 */
#include <iostream>

#define COUNT 10

template <typename T>
struct Node {
    Node(T data) {this->data = data;}
    T data;
    int height = 0;
    Node* parent = 0;
    Node* left = 0;
    Node* right = 0;
};

template <typename T>
class BST {

    // Outputs keys of the tree in sorted order.
    template <typename S>
    friend std::ostream& operator<<(std::ostream&, const BST<S>&);

    // Outputs keys of the tree via recursive inorder traversal. Called
    // from stream insertion operator.
    template <typename S>
    friend void print(std::ostream&, Node<S>*);

public:
    // Constructor
    BST() {root = NULL; size = 0;}
    // Destructor
    ~BST<T>() {remove(root);}
    // Insert function
    virtual void insert(T data);
    // height function
    int height() {return height(root);}

    // Added by me. Hopefully you understand this was needed to filter out duplicates.
    int getSize(){return size;}

protected:
    Node<T>* root;
    void remove(Node<T>*); // Recursively deallocates tree.
    int height(Node<T>*); // Returns height of node (-1 if NULL)

    // I added the following function and field.
    void updateHeight(Node<T>*);
    int size;
};
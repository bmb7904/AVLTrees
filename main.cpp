/*
 * A c++ program that will test the implementation of both a Binary Search Tree and an
 * AVL tree and compare their heights experimentally. I originally was using the
 * recursively defined height function to update heights of all nodes for each
 * insertion, and my program never got to the end because it was taking too long. At
 * the last minute, I had a revelation. First, after adding a new node to a tree, the
 * only heights that change are the ancestors of the node added. Just checking these
 * can save computation. Secondly, I can write a non-recursive function, and use a
 * process similar to bottom-up dynamic programming. I'm not sure if that is the correct
 * terminology, but it "feels" like bottom-up dynamic programming to remove recursion
 * in updating all heights. It is based on the fact that the height of any node, n,
 * can be defined as: 1 + max(height(left child), height(right child)).
 * This new function, called, updateHeight(Node<T>* n) was
 * added to the BST class. I checked both BST and AVL trees repeatedly with our AVL
 * tree tool from the website, and it constructs AVL trees perfectly for every test I
 * ran. I also added a size field and a getSize() function in order to check the size
 * of the tree(# of nodes). This is needed because I am accounting for duplicates while
 * entering random numbers. Please use my header files when compiling this program, as
 * there are changes and it won't work correctly without them. This program takes about
 * 20 seconds to run on my home PC, but on repl.it it takes a little over a minute.
 *
 * @author: Brett Bernardi
 * @date November 10, 2020
 */
#include "avl_tree.cpp"
#include "math.h"
#include <iostream>
#include <stdlib.h>
#include <limits>
#include <iomanip>

using namespace std;

template <typename T>
void insertRandomElements(BST<T> *p1, BST<T>* p2, int n);

template <typename T>
void insertRandomElements2(BST<T> *p1, int n);

int main()
{
    srand(time(0));

    BST<int> *bst;
    BST<int> *avl;

    cout << endl;
    cout <<"Heights of non-rebalancing BSTs and AVL trees with random keys:\n\n" << endl;
    for(int i = 1; i <= 20; i++)
    {
        bst = new BST<int>();
        avl = new AvlTree<int>();
        insertRandomElements(bst, avl, pow(2,i));
        cout << "2^" <<setw(5) << left << i << setw(4) << right << bst->height() << setw
        (8) << right << avl->height() << endl;
        delete bst;
        delete avl;
   }

}

/**
 * Adds n elements to two BST<T> trees(or derived AvlTrees). Doesn't stop until the
 * size of each tree (number of nodes) is equal to n. Becuase my trees don't allow
 * duplicates, I wanted to make sure they were filled up completely.
 *
 */
template <typename T>
void insertRandomElements(BST<T> *p1, BST<T>* p2, int n)
{

    while(p1->getSize() < n)
    {
        double temp = rand() % numeric_limits<int>::max() + 1;
        p1->insert(temp);
        p2->insert(temp);
    }

}



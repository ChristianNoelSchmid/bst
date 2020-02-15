/* Christian Schmid
 * bst - bst.h
 * Implementation of a Binary Search Tree
 * using recursion for traversal, insertion,
 * and removal
 */

#include<iostream>

namespace bst
{
    /* DEFINITION OF BST
     ------------------------- */

    /* Node struct
     * An definition of the inner-node of a BST. Includes
     * a data element, and connected child nodes. Template
     * type, to allow multiple types of values */
    template<class T>
    struct BSTNode
    {
        T element;
        BSTNode<T> *left;
        BSTNode<T> *right;

        BSTNode();
        BSTNode(const T & elem);

        BSTNode(const BSTNode<T> & source);
        ~BSTNode();
    };

    template<class T>
    struct BSTNode<T*>
    {
        T* element;
        BSTNode<T> *left;
        BSTNode<T> *right;
        
        BSTNode();
        BSTNode(const BSTNode<T*> & source);
        BSTNode(const T & elem);
        BSTNode(const T *elem);
        ~BSTNode();
    };

    class BST { };

    /* IMPLEMENTATION OF BST
     * included in header, to avoid templatiie
     * inclusion issues */
    template<class T> BSTNode<T>::BSTNode() : element(NULL), left(NULL), right(NULL) { } 

    template<class T> BSTNode<T*>::BSTNode() : left(NULL), right(NULL)
    {
        element = NULL;
    }
    template<class T> BSTNode<T*>::BSTNode(const BSTNode<T*> & source)
    {
        element = new T(*(source.element)); 
        left = right = NULL;
    }

    template<class T> BSTNode<T*>::BSTNode(const T & elem)
    {
        element = new T(elem);
        left = right = NULL;
    }

    template<class T> BSTNode<T*>::BSTNode(const T *elem)
    {
        element = new T(*elem);
        left = right = NULL;
    }

    template<class T> BSTNode<T>::BSTNode(const T & elem) : left(NULL), right(NULL)
    {
        if(std::is_fundamental<T>())
        {
            element = elem;
        }
        else
        {
            element = T(elem);
        }
    }

    template<class T> BSTNode<T*>::~BSTNode()
    {
        delete element;
        delete left;
        delete right;

        left = right = NULL;
    }

    template<class T> BSTNode<T>::~BSTNode() 
    {
        delete left;
        delete right;
    }
}
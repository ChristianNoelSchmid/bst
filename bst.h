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
     * type, to allow multiple types of values 
     * Node struct has two separate templates - one for generics
     * of non-pointer types, and one for pointer types. This is
     * done to ensure that dynamic casting is possible for the BST.
     */

    // Non-pointer type
    template<class T> struct BSTNode
    {
        T element;
        BSTNode<T> *left;
        BSTNode<T> *right;

        BSTNode();
        BSTNode(const T & elem);

        BSTNode(const BSTNode<T> & source);
        ~BSTNode();
    };

    template<class T> class BST
    {
        public:
            BST();
            ~BST();

            int vtx_count() const;

            void insert(const T & element);
            bool remove(const T & element);

            void print() const;

        private:
            BSTNode<T> *root;
            int vertex_count;

            void insert_helper(const T & element, BSTNode<T> *& current);
            bool remove_helper(const T & element, BSTNode<T> *& current);

            void print_helper(const BSTNode<T> *current) const;
            BSTNode<T> *& get_leftmost(BSTNode<T> *& current);
    };

    // Pointer type
    template<class T> struct BSTNode<T*>
    {
        T* element;
        BSTNode<T> *left;
        BSTNode<T> *right;
        
        BSTNode();
        BSTNode(const BSTNode<T*> & source);
        BSTNode(T *elem);
        ~BSTNode();
    };

    template<class T> class BST<T*>
    { 

    };

    /* IMPLEMENTATION OF BST
     * included in header, to avoid templatiie
     * inclusion issues */
    /* Non-Pointer Type */
    template<class T> BSTNode<T>::BSTNode() : element(NULL), left(NULL), right(NULL) { } 

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

    template<class T> BSTNode<T>::~BSTNode() 
    {
        delete left;
        delete right;
    }

    template<class T> BST<T>::BST() : root(NULL), vertex_count(0) { }
    template<class T> BST<T>::~BST() { delete root; root = NULL; }

    template<class T> int BST<T>::vtx_count() const { return vertex_count; }

    template<class T> void BST<T>::insert(const T & element)
    {
        insert_helper(element, root);
    }
    template<class T> bool BST<T>::remove(const T & element)
    {
        return remove_helper(element, root); 
    }
    template<class T> void BST<T>::print() const
    {
        print_helper(root);    
        std::cout << std::endl;
    }

    template<class T> void BST<T>::insert_helper(const T & element, BSTNode<T> *& current)
    {
        if(current == NULL) 
        {
            current = new BSTNode<T>(element);
            ++vertex_count;
            return;
        }

        if(current->element < element)
        {
            insert_helper(element, current->left);
        }
        else
        {
            insert_helper(element, current->right);
        }
    }

    template<class T> bool BST<T>::remove_helper(const T & element, BSTNode<T> *& current)
    {
        if(current == NULL) return false;     

        if(current->element == element)
        {
            if(current->left == NULL && current->right == NULL)
            {
                delete current;
                current = NULL;
            }
            else if((current->left == NULL) ^ (current->right == NULL))
            {
                BSTNode<T> *temp = current->right == NULL ? current->left : current->right;
                current->left = current->right = NULL;

                delete current;

                current = temp;
            } 
            else
            {
                BSTNode<T> *right = current->right;     
                if(right->left == NULL || right->right == NULL)
                {
                    current->element = T(right->element);
                    current->right = right->right == NULL ? right->left : right->right;

                    right->right = right->left = NULL;
                    delete right;
                }

                else
                {
                    BSTNode<T> *ios = get_leftmost(right->left);    
                    current->element = T(ios->element);

                    BSTNode<T> *temp = ios; 
                    ios = ios->right;

                    temp->left = temp->right = NULL;
                    delete temp;
                }
            }

            --vertex_count;
            return true;
        }
        else if(current->element < element)
        {
            return remove_helper(element, current->left);
        }
        else
        {
            return remove_helper(element, current->right);
        }
    }

    template<class T> void BST<T>::print_helper(const BSTNode<T> *current) const
    {
        if(current == NULL) { return; }

        print_helper(current->left);
        std::cout << current->element << ", ";
        print_helper(current->right);
    }

    template<class T> BSTNode<T> *& BST<T>::get_leftmost(BSTNode<T> *& current)
    {
        if(current->left == NULL)
        {
            return current;
        }
        return get_leftmost(current->left);
    }


    /* Pointer Type */
    template<class T> BSTNode<T*>::BSTNode() : left(NULL), right(NULL)
    {
        element = NULL;
    }
    template<class T> BSTNode<T*>::BSTNode(const BSTNode<T*> & source)
    {
        element = new T(*(source.element)); 
        left = right = NULL;
    }

    template<class T> BSTNode<T*>::BSTNode(T *elem)
    {
        element = elem;
        left = right = NULL;
    }

    template<class T> BSTNode<T*>::~BSTNode()
    {
        delete element;
        delete left;
        delete right;

        left = right = NULL;
    }    
}
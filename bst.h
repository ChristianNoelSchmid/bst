/* Christian Schmid
 * bst - bst.h
 * Implementation of a Binary Search Tree
 * using recursion for traversal, insertion,
 * and removal
 */

#include<iostream>
#include<fstream>

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
        T element; // The value of type T being stored in the node
        BSTNode<T> *left; // The left child
        BSTNode<T> *right; // The right child

        BSTNode(); // Default Constructor
        BSTNode(const T & elem); // Primary Constructor - sets element to supplied value 

        BSTNode(const BSTNode<T> & source); // Copy Constructor -- deep copy of all elements
        ~BSTNode(); // Destructor
    };

    template<class T> class BST
    {
        public:
            BST(); // Default Constructor
            BST(const BST & source); // Copy Constructor
            ~BST(); // Destructor

            int vtx_count() const; // The # of vertices in the BST

            // Insert a new element, in order, into the BST
            void insert(const T & element); 
            // Remove an element from the BST, if it exists. Return true
            // if removal is successful, or false otherwise
            bool remove(const T & element);

            // Prints all elements of the BST in order
            void print() const;

            // Converts the BST to a .dot file, saving to
            // supplied filename
            void to_dot(std::string filename) const;

        private:
            BSTNode<T> *root; // Root of the Tree
            int vertex_count; // # of vertices

            void insert_helper(const T & element, BSTNode<T> *& current);
            bool remove_helper(const T & element, BSTNode<T> *& current);

            void print_helper(const BSTNode<T> *current) const;
            BSTNode<T> *& get_leftmost(BSTNode<T> *& current);

            void to_dot_helper(std::ofstream & file_out, const BSTNode<T> *current) const;
    };

    // Pointer type
    template<class T> struct BSTNode<T*>
    {
        T* element; // Pointer-value of type T* being stored in node
        BSTNode<T> *left; // left child
        BSTNode<T> *right; // right child
        
        BSTNode();
        BSTNode(const BSTNode<T*> & source);
        BSTNode(T *elem);
        ~BSTNode();
    };
    
    /* IMPLEMENTATION OF BST
     * included in header, to avoid templatiie
     * inclusion issues */

    /* Non-Pointer Type */
    /* BSTNode */
    // Default Constructor
    template<class T> BSTNode<T>::BSTNode() : element(NULL), left(NULL), right(NULL) { } 

    // Primary Constructor
    template<class T> BSTNode<T>::BSTNode(const T & elem) : left(NULL), right(NULL)
    {
        // If the element is a primitive type, simply set element to elem.
        // Otherwise call the element's Copy Constructor
        if(std::is_fundamental<T>())
        {
            element = elem;
        }
        else
        {
            element = T(elem);
        }
    }

    // Destructor - recursively deletes each BSTNode's children
    template<class T> BSTNode<T>::~BSTNode() 
    {
        delete left;
        delete right;
    }

    // Default Constructor - initializes data
    template<class T> BST<T>::BST() : root(NULL), vertex_count(0) { }
    // Destructor - deletes root, which recursively deletes all vertices
    template<class T> BST<T>::~BST() { delete root; root = NULL; }

    // Returns the # of vertices in the BST, using cached vertex_count
    template<class T> int BST<T>::vtx_count() const { return vertex_count; }

    // Insert a new element, in order, into the BST
    template<class T> void BST<T>::insert(const T & element)
    {
        // Call helper function
        insert_helper(element, root);
    }

    // Remove an element from the BST, if it exists. Return true
    // if removal is successful, or false otherwise
    template<class T> bool BST<T>::remove(const T & element)
    {
        // Return the helper function result
        return remove_helper(element, root); 
    }

    // Prints all elements of the BST in order
    template<class T> void BST<T>::print() const
    {
        // Call the helper function, followed by a newline
        print_helper(root);    
        std::cout << std::endl;
    }

    // Searches the BST for the correct position to insert new element, traversive each
    // subnode through the process
    template<class T> void BST<T>::insert_helper(const T & element, BSTNode<T> *& current)
    {
        // If current is NULL, correct node has been reached
        // Set current to new BSTNode with element value
        if(current == NULL) 
        {
            current = new BSTNode<T>(element);
            ++vertex_count;
            return;
        }

        if(element < current->element)
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

    template<class T> void BST<T>::to_dot(std::string filename) const
    {
        std::ofstream file_out = std::ofstream();
        file_out.open(filename);

        if(file_out)
        {
            for(int i = 0; i < 4; ++i) filename.pop_back();

            file_out << "digraph " << filename << " {\n";
            to_dot_helper(file_out, root);
            file_out << "}";

            file_out.close();        
        }
    }

    template<class T> void BST<T>::to_dot_helper(std::ofstream & file_out, const BSTNode<T> *current) const
    {
        if(current != NULL)
        {
            if(current->left != NULL)
            {
                file_out << "\"" << current->element << "\" -> \"" << current->left->element << "\";\n";
                to_dot_helper(file_out, current->left);
            }
            if(current->right != NULL)
            {
                file_out << "\"" << current->element << "\" -> \"" << current->right->element << "\";\n";
                to_dot_helper(file_out, current->right);
            }
        }
    }


    /* Pointer Type */
    template<class T> BSTNode<T*>::BSTNode() : left(NULL), right(NULL)
    {
        element = NULL;
    }
    template<class T> BSTNode<T*>::BSTNode(const BSTNode<T*> & source)
    {
        element = new typeof(source)(*(source.element)); 
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
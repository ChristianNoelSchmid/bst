#include<cstring>
#include <iostream>
#include <string>
#include <vector>

#include "account.h"
#include "bst.h"

int main(int argc, char **argv)
{
    using namespace bst;
    using namespace std;

    BST<string> bst = BST<string>();
    bst.insert("Hello");
    bst.insert("World!");
    bst.insert("My");
    bst.insert("Name");
    bst.insert("Is");
    bst.insert("Oliver!");
    bst.insert("And");
    bst.insert("I");
    bst.insert("Have");
    bst.insert("Two");
    bst.insert("Masters,");
    bst.insert("Alyssa");
    bst.insert("Chris!");

    bst.print();

    if(argc > 1 && strcmp(argv[1], "--dot") == 0)
    {
        bst.to_dot(argv[2]); 
    }

    return 0;
}
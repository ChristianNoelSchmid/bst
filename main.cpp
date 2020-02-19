#include <iostream>
#include <string>
#include <vector>

#include "account.h"
#include "bst.h"

int main()
{
    using namespace bst;
    using namespace std;

    BST<string> bst = BST<string>();
    bst.insert("Hello");
    bst.insert("World!");
    bst.insert("My");
    bst.insert("name");
    bst.insert("Is");
    bst.insert("Oliver!");
    bst.insert("Nab");
    bst.insert("Zanzibar");

    cout << "Initial BST: "; bst.print(); cout << "Vertex count: " << bst.vtx_count() << endl;
    cout << "Removing Nab..."; bst.remove("Nab");
    bst.print(); cout << "Vertex count: " << bst.vtx_count() << endl;
    cout << "Removing Hello..."; bst.remove("Hello");
    bst.print(); cout << "Vertex count: " << bst.vtx_count() << endl;
    cout << "Removing Oliver!..."; bst.remove("Oliver!");
    bst.print(); cout << "Vertex count: " << bst.vtx_count() << endl;
    cout << "Removing Is..."; bst.remove("Is");
    bst.print(); cout << "Vertex count: " << bst.vtx_count() << endl;
   
    return 0;
}
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

    BST<Account*> accounts = BST<Account*>();
    accounts.insert(new SavingsAccount(10.0, "Christian", 0.23));

    if(argc > 1 && strcmp(argv[1], "--dot") == 0)
    {
        accounts.to_dot(argv[2]); 
    }

    return 0;
}
#include <iostream>
#include <string>
#include <vector>

#include "account.h"
#include "bst.h"
using namespace bst;

int main()
{
    BSTNode<Account*> account = BSTNode<Account*>(new SavingsAccount(12.75, "Chris", 0.045));
    account.element->print_info();
   
    return 0;
}
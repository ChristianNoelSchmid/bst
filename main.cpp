#include <iostream>
#include <string>
#include <vector>

class Account
{
    protected:
        std::string name;

    public:
        virtual ~Account() { }
        virtual void print_info()
        {
            std::cout << "Account " << name << std::endl;
        }
};

class SavingsAccount : public Account
{
    private:
        float savings;

    public:
        SavingsAccount(float sav) : savings(sav) { }

        void print_info() override
        {
            Account::print_info();
            std::cout << "Savings of " << savings << std::endl;
        }
};

#include "bst.h"
using namespace bst;

int main()
{
    using namespace std;

    vector<Account*> accounts = vector<Account*>();
    accounts.push_back(new SavingsAccount(12.45));

    accounts[0]->print_info();
   
    return 0;
}
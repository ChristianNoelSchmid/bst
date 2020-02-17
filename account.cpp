#include "account.h"

Account::Account() : amount(0.0f), name_of_owner("") { }
Account::Account(float am, std::string owner) : amount(am), name_of_owner(owner) { }
Account::~Account() { }
void Account::print_info()
{
    std::cout << "Account for " << name_of_owner << std::endl;
    std::cout << "\t- $" << amount << " in this account." << std::endl;
}

SavingsAccount::SavingsAccount() : Account(), interest(0.0) { }
SavingsAccount::SavingsAccount(float am, std::string owner, float intrst) : Account(am, owner), interest(intrst) { }
void SavingsAccount::print_info()
{
    Account::print_info();
    std::cout << "\t- %" << (interest * 100.0) << " interest" << std::endl;
}
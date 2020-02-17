#include<iostream>
#include<string>

class Account 
{
    public:
        Account();
        Account(float am, std::string owner);
        
        virtual ~Account();
        virtual void print_info();

    protected:
        float amount;
        std::string name_of_owner;
};

class SavingsAccount : public Account
{
    public:
        SavingsAccount();
        SavingsAccount(float am, std::string owner, float interest);
        void print_info() override;

    private:
        float interest;
};

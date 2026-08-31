#include "Account.h"

bool Account::deposit(double amount) {
    bool isSuccessful = true;

    if (!isValidAmount(amount)) 
    {
        isSuccessful = false;
    }
    else
    {
        balance += amount;
        
        Transaction transaction(Constants::TransactionType::DEPOSIT, amount, balance);
        transactions.push_back(transaction); 
    }
    
    return isSuccessful;
}

bool Account::withdrawal(double amount) {
    bool isSuccessful = true;

    if (!isValidAmount(amount) || balance < amount) 
    {
        isSuccessful = false;
    }
    else
    {
        balance -= amount;
    
        Transaction transaction(Constants::TransactionType::WITHDRAWAL, amount, balance);
        transactions.push_back(transaction); 
    }
    
    return isSuccessful;
}

std::vector<Transaction> Account::getLastTransactions(int count) {
    int size = transactions.size();
    int start = (size > count) ? size - count : 0;
    return std::vector<Transaction>(transactions.begin() + start, transactions.end());
}

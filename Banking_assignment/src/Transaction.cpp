#include "Transaction.h"
#include "Constants.h"

long Transaction::transactionIdCounter = Constants::INITIAL_TRANSACTION_ID;

Transaction::Transaction(Constants::TransactionType transactionType, 
                        double amount, double postBalance)
    : type(transactionType), amount(amount), 
      postTransactionBalance(postBalance) {
    id = transactionIdCounter++; 
}

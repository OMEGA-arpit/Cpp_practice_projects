#include "BankingSystem.h"
#include "Bank.h"

int main() {
    Bank bank;
    BankingSystem system(&bank);
    system.execute();
    return 0;
}

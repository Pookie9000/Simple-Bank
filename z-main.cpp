#include "Bank.h"
/*
Final notes:
*Sometimes the console has invisible text, I am yet to find the cause. Press any key to make it show up again. 

*probably missed a few contingencies

*What matters is I tried my best.
*/
int main() {
Bank bank;
BankAccount accounts;
CheckingAccount checkingAccounts;
SavingsAccount savingsAccounts;


bank.createBank();
bank.bankMenu(accounts, savingsAccounts, checkingAccounts);

    cout << "Goodbye!" << endl;
  return 0;
}
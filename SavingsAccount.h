#include "CheckingAccount.h"

class SavingsAccount {

public:
//generates a random savings account number
void savingsAccountNumberGenerator() {
  int randomNumber = rand() % 1000;
  savingsAccountNumberHolder = "SAV" + to_string(randomNumber);
}

//creates a savings account. takes ssn and object of Saings Account as input.
void createSavingsAccount(string ssn, SavingsAccount savAccountObj);

//clears a specifc savings account. takes ssn and savings account number to do so.
void clearSavingsAccount(string ssn, string savingsAccountNumber);

//purge function that clears all savings accounts associate with ssn. takes ssn as input to do so.
void purgeSavingsAccount(string ssn);

//tracks total number of savings sub-accounts created.
void totalNumSavingsAccounts() {
  cout << "Number of Savings Accounts: " << savAccounts.size() << endl;
  cout << endl;
}

//tracks number of savings sub-accounts associated with a bank account. takes ssn as input.
int trackNumSavingsAccounts(string ssn) {
  int total = 0;
  for (auto& savAccount : savAccounts) {
    if (savAccount.first == ssn) {
      total = total + 1;
    }
  }
  return total;
}

//displays every savings sub-account created within a bank account. takes ssn as input to do so.
void allSavingsAccounts(string ssn);

//provides aggregated balance of all saving accounts within a bank account. takes ssn as input. 
int briefSavingsAccountInfo(string ssn);

//add balances of every sub account created.
double aggregatedBalOfAll() {
  double total = 0;
  for (auto& savAccount : savAccountNumbers) {
    total = total + savAccount.second;
  }
  return total;
}

//takes ssn as input. Checks if Savings account exists. Used for potential errors.
int accountExists(string ssn) {
  if (savAccounts.find(ssn) == savAccounts.end()) {
    return -1;
  } else {
    return 0;
  }
}

//main hub for savings account. shows all actions a user can take for their savings account. takes ssn as input.
void savingsAccountMenu(string ssn);



private:
map<string, string> savAccounts; //Stores (ssn, SAV1000)
map<string, double> savAccountNumbers; //Store(SAV1000, balance)
string savingsAccountNumberHolder; //temperarily holds savings account number e.g. SAV1000
};

void SavingsAccount::createSavingsAccount(string ssn, SavingsAccount savAccountObj)  {
  double initialBalance;
  double theLie = 100;
savingsAccountNumberGenerator();
  if (savAccounts.find(ssn) == savAccounts.end()) {
    cout << "Congratulations! You have opened a new Savings Account. $100 will be added to your balance." << endl;
    cout << endl;
    cout << "Enter the initial balance: ";
    cin >> initialBalance;
    if (initialBalance < 0) {
      cout << "Invalid amount." << endl;
    } else {
      initialBalance = initialBalance + theLie;
    cout << "Current balance of " << savingsAccountNumberHolder << ":" << initialBalance << endl;
    savAccounts.emplace(ssn, savingsAccountNumberHolder);
    savAccountNumbers.emplace(savingsAccountNumberHolder, initialBalance);
      cout << endl;
  }
} else if (savAccounts.find(ssn) != savAccounts.end()) {
    cout << "Enter initial balance: " << endl;
    cin >> initialBalance;
    if (initialBalance < 0) {
      cout << "Invalid amount." << endl;
    } else {
      cout << "Current balance of " << savingsAccountNumberHolder << ":" << initialBalance << endl;
savAccounts.emplace(ssn, savingsAccountNumberHolder);      savAccountNumbers.emplace(savingsAccountNumberHolder, initialBalance);
      cout << endl;
    }
  }
}

void SavingsAccount::clearSavingsAccount(string ssn, string savingsAccountNumber) {
  char choice = ' ';
  cout << "Are you sure you want to close this account? (Y/N): ";
  cin >> choice;
  if (choice == 'Y' || choice == 'y') {
    savAccounts.erase(savingsAccountNumber);
    savAccountNumbers.erase(ssn);
    cout << "Account was successfully closed." << endl;
    cout << endl;
  }
  if (choice == 'N' || choice == 'n') {
    cout << "Good choice..." << endl;
    cout << endl;
  }
}

void SavingsAccount::purgeSavingsAccount(string ssn) {
  for (auto it = savAccounts.begin(); it != savAccounts.end(); it++) {
    if (it->first == ssn) {
      savAccountNumbers.erase(it->second);
      savAccounts.erase(it->first);
    }
  }
}

void SavingsAccount::allSavingsAccounts(string ssn) {
  cout << "Savings Accounts: " << endl;
  for (auto& savAccount : savAccounts) {
    cout << "Account Holder: " << ssn << endl;
    cout << "SSN: " << savAccount.second << endl;
    cout << "Savings Account Number: " << savAccountNumbers.at(savAccount.second) << endl;
    cout << endl;
  }
}

int SavingsAccount::briefSavingsAccountInfo(string ssn) {
  int total = 0;
  for (auto& savAccount : savAccounts) {
    if (savAccount.first == ssn) {
      total = total + savAccountNumbers.at(savAccount.second);
    }
  }
  return total;
}





void SavingsAccount::savingsAccountMenu(string subAccountNum) {
  char choice = ' ';
  if (savAccountNumbers.find(subAccountNum) == savAccountNumbers.end()) {
    cout << "Account does not exist." << endl;
  } else {
  while (choice != 'X' || choice != 'x') {
    cout << "Eligible services for sub-account " << subAccountNum << ":" << endl;
    cout << "  D -- Deposit" << endl;
    cout << "  W -- Withdraw" << endl;
    cout << "  X -- Exit" << endl;
    cout << "Please enter your selection: ";
    cin >> choice;
cout << endl;

    if (choice == 'D' || choice == 'd') {
      double amount;
      cout << "Enter the amount to deposit: ";
      cin >> amount;
      if (amount < 0) {
        cout << "If you put a negative you might as well withdrawl, silly." << endl;
        cout << endl;
      } else {
        savAccountNumbers.at(subAccountNum) = savAccountNumbers.at(subAccountNum) + amount;
        cout << "Deposit was successful." << endl;
        cout << endl;
      }
}

    if (choice == 'W' || choice == 'w') {
      double amount;
      cout << "Enter the amount to withdraw: ";
      cin >> amount;
      if (amount < 0) {
        cout << "I work with only positives digits! Try again, loser >:3" << endl;
        cout << endl;
      } else {
        savAccountNumbers.at(subAccountNum) = savAccountNumbers.at(subAccountNum) - amount;
        cout << "Withdrawl was successful." << endl;
        cout << "Current balance of " << subAccountNum <<  ": "; 
        savAccountNumbers.at(subAccountNum);
        cout << endl;
        cout << endl;
      }
    }

    if (choice == 'X' || choice == 'x') {
      cout << "End of service for sub-account " << subAccountNum << endl;
      cout << endl;
      break;
    }
  }
  }
}
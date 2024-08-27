#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class CheckingAccount {

public:
CheckingAccount() {}
void checkingAccountNumberGenerator();

//creates a checking account. takes ssn and object of checking account as input.
void createCheckingAccount(string ssn, CheckingAccount chkAccountObj);

//clears a specific checking account. takes ssn and checking account number to do so.
void clearCheckingAccount(string ssn, string subAccountNum);

//purge function that clears all checking accounts associate with ssn. takes ssn as input to do so.
void purgeCheckingAccount(string ssn);

//tracks total number of checking acccounts.
void numCheckingAccounts();

//tracks number of checking accounts within a bank account. takes ssn to do so.
int trackNumCheckingAccounts(string ssn);

//displays all checking accounts within a bank account. takes ssn to do so.
void allCheckingAccounts(string ssn);

//displays aggregated balance of all checking accounts within a bank account. takes ssn to do so.
int briefCheckingAccountInfo(string ssn);

//displays aggregated balance of all checking accounts.
double aggregatedBalOfAll() {
  double total = 0;
  for (auto& chckAccount : chekAccountNumbers) {
    total = total + chckAccount.second;
  }
  return total;
}

//functions that modifies lock sttus of a given checking account. takes checking account number and your 'choice' ('L or 'U) to do so.
void changeLockStatus(string subAccountNum, char choice);

//function that checks max capacity and then adds sum to exisitng checking account. takes checking account number to do so.
void deposit(string subAccountNum);

//function that checks lock status and then withdraws sum from exisitng checking account. takes checking account number to do so.
void withdraw(string subAccountNum);

//function that modifies maximum capacity of a checking account. takes checking account number to do so.
void modifyCapacity(string subAccountNum);

//main menu for checking account. takes sub-account name as input.
void checkingAccountMenu(string subAccountNum);



private:
map<string, string> chekAccounts; //Stores (ssn, CHK6000)
map<string, double> chekAccountNumbers; //Store (CHK6000, balance)
map<string, int> chekCapacities; //Stores (CHK6000, maxCapacity) keeps track of capacity set for specific checking sub-accounts.
map<string, bool> chekLocks; // Stores (CHK6000, locked) keeps track of whether a specific checking sub-account is locked or unlocked.
string checkingAccountNumberHolder;

};

void CheckingAccount::checkingAccountNumberGenerator() {
  int randomNumber = rand() % 6000;
  checkingAccountNumberHolder = "CHK" + to_string(randomNumber);
}

void CheckingAccount::createCheckingAccount(string ssn, CheckingAccount chkAccountObj) {
  string checkingAccountNumber;
  double initialBalance;
  int maxCapacity;
  bool locked;
  cout << "Enter the initial balance: ";
  cin >> initialBalance;
  cout << "Enter the desired maximum capacity: ";
  cin >> maxCapacity;
  cout << "Initial state: (Unlocked) ";
    locked = true;
    checkingAccountNumberGenerator();
    chekAccounts.emplace(ssn, checkingAccountNumberHolder);
    chekAccountNumbers.emplace(checkingAccountNumberHolder, initialBalance);
    chekCapacities.emplace(checkingAccountNumberHolder, maxCapacity);
    chekLocks.emplace(checkingAccountNumberHolder, locked);
    cout << endl;
    cout << "A new Checking Sub-Account " << checkingAccountNumberHolder << " was successfully created." << endl;
  cout << endl;
  }

void CheckingAccount::clearCheckingAccount(string ssn, string subAccountNum) {
  if (chekAccounts.find(ssn) == chekAccounts.end()) {
    cout << "Account does not exist." << endl;
  } else {
      char choice = ' ';
      cout << "Are you sure you want to close this account? (Y/N): ";
      cin >> choice;
      if (choice == 'Y' || choice == 'y') {
        chekLocks.erase(subAccountNum);
        chekCapacities.erase(subAccountNum);
        chekAccountNumbers.erase(subAccountNum);
        chekAccounts.erase(ssn);
        cout << "Account was successfully closed." << endl;
        cout << endl;
      }
      if (choice == 'N' || choice == 'n') {
        cout << "Good choice..." << endl;
        cout << endl;
      }
    }
}

void CheckingAccount::purgeCheckingAccount(string ssn) {
  for (auto it = chekAccounts.begin(); it != chekAccounts.end(); it++) {
    if (it->first == ssn) {
      chekCapacities.erase(it->second);
      chekLocks.erase(it->second);
      chekAccountNumbers.erase(it->second);
      chekAccounts.erase(it->first);
    }
  }
}

void CheckingAccount::numCheckingAccounts() {
  cout << "Number of Checking-Accounts: " << chekAccounts.size() << endl;
  cout << endl;
}

int CheckingAccount::trackNumCheckingAccounts(string ssn) {
  int total = 0;
  for (auto& chekAccount : chekAccounts) {
    if (chekAccount.first == ssn) {
      total = total + 1;
    }
  }
  return total;
}

void CheckingAccount::allCheckingAccounts(string ssn) {
  for (auto it = chekAccounts.begin(); it != chekAccounts.end(); it++) {
    if (it->first == ssn) {
      cout << "Sub-Account Number: " << it->second << endl;
      cout << "Balance: " << chekAccountNumbers.at(it->second) << endl;
      cout << "Maximum Capacity: " << chekCapacities.at(it->second) << endl;
      cout << "Lock Status: ";
      if (chekLocks.at(it->second) == true) {
        cout << "Locked" << endl;
      } else {
        cout << "Unlocked" << endl;
      }
      cout << endl;
    }
  }
} 

int CheckingAccount::briefCheckingAccountInfo(string ssn) {
  int total = 0;
  for (auto& chkAccount : chekAccounts) {
    if (chkAccount.first == ssn) {
      total = total + chekAccountNumbers.at(chkAccount.second);
    }
  }
  return total;
}

void CheckingAccount::changeLockStatus(string subAccountNum, char choice) {
  if (chekAccountNumbers.find(subAccountNum) == chekAccountNumbers.end()) {
    cout << "Account does not exist." << endl;
  } else {
    if (choice == 'U' || choice == 'u') {
      chekLocks.at(subAccountNum) = true;
      cout << "The sub-account " << subAccountNum << " is unlocked now!" << endl;
      cout << endl;
    } else if (choice == 'L' || choice == 'l') {
      chekLocks.at(subAccountNum) = false;
      cout << "The sub-account " << subAccountNum << " is locked now!" << endl;
      cout << endl;
    }
  }
}

void CheckingAccount::deposit(string subAccountNum) {
  if (chekAccountNumbers.find(subAccountNum) == chekAccountNumbers.end()) {
    cout << "Account does not exist." << endl;
  } else {
    double amount;
    cout << "Enter the amount to deposit: ";
    cin >> amount;
    if (amount < 0) {
      cout << "If you put a negative you might as well withdrawl, silly." << endl;
      cout << endl;
    } else if (amount > chekCapacities.at(subAccountNum)) {
      cout << "Deposit amount exceeds maximum capacity." << endl;
      cout << "  max capacity set at: " << chekCapacities.at(subAccountNum) << endl;
      cout << endl;
    } else if (chekLocks.at(subAccountNum) == false) {
      cout << "Account Locked. Deposit not allowed." << endl;
      cout << endl;
    } else if (chekLocks.at(subAccountNum) == true && amount < chekCapacities.at(subAccountNum)) {
      chekAccountNumbers.at(subAccountNum) = chekAccountNumbers.at(subAccountNum) + amount;
      cout << "Deposit was successful." << endl;
      cout << endl;
    }
  }
}

void CheckingAccount::withdraw(string subAccountNum) {
  if (chekAccountNumbers.find(subAccountNum) == chekAccountNumbers.end()) {
    cout << "Account does not exist." << endl;
  } else {
    double amount;
    cout << "Enter the amount to withdraw: ";
    cin >> amount;
    if (amount < 0) {
      cout << "Positive numbers only, please." << endl;
      cout << endl;
    } else if (amount > chekCapacities.at(subAccountNum)) {
      cout << "Withdrawl amount exceeds maximum capacity." << endl;
      cout << "  max capacity set at: " << chekCapacities.at(subAccountNum) << endl;
      cout << endl;
    } else if (chekLocks.at(subAccountNum) == false) {
      cout << "Account Locked. Withdrawl not allowed." << endl;
    } else if (chekLocks.at(subAccountNum) == true && amount < chekCapacities.at(subAccountNum)) {
      chekAccountNumbers.at(subAccountNum) = chekAccountNumbers.at(subAccountNum) - amount;
      cout << "Withdrawl was successful." << endl;
    cout << endl;
    }
  }
}

void CheckingAccount::modifyCapacity(string subAccountNum) {
  if (chekAccounts.find(subAccountNum) == chekAccounts.end()) {
    cout << "Account does not exist." << endl;
  } else {
    int amount;
    cout << "  Current max capacity: ";
    chekCapacities.at(subAccountNum);
    cout << endl;
    cout << "Enter new capacity: ";
    cin >> amount;
    if (amount < 0) {
      cout << "Positive numbers only, please." << endl;
    } else if (amount >= 0) {
      chekCapacities.at(subAccountNum) = amount;
      cout << "New max capacity set to: ";
      chekCapacities.at(subAccountNum);
      cout << endl;
    }
  }
}

void CheckingAccount::checkingAccountMenu(string subAccountNum) {
  char choice = ' ';
  if (chekAccountNumbers.find(subAccountNum) == chekAccountNumbers.end()) {
    cout << "Account does not exist." << endl;
    cout << endl;
  } else { 
    while (choice != 'X' || choice != 'x') {
    cout << "Eligible services for sub-account " << subAccountNum << ":" << endl;
    cout << "  D -- Deposit" << endl;
    cout << "  W -- Withdraw" << endl;
    cout << "  C -- Max Capacity" << endl;
    cout << "  L -- Lock Sub-Account" << endl;
    cout << "  U -- Unlock Sub-Account" << endl;
    cout << "  X -- Exit" << endl;
    cout << "Please enter your selection: ";
    cin >> choice;
    cout << endl;
      
      if (choice == 'D' || choice == 'd') {
        deposit(subAccountNum);
      }
      if (choice == 'W' || choice == 'w') {
        withdraw(subAccountNum);
      }
      if (choice == 'C' || choice == 'c') {
        modifyCapacity(subAccountNum);
      }
      if (choice == 'L' || choice == 'l') {
        changeLockStatus(subAccountNum, choice);
      }
      if (choice == 'U' || choice == 'u') {
        changeLockStatus(subAccountNum, choice);
      }
      if (choice == 'X' || choice == 'x') {
        cout << "End of service for sub-account " << subAccountNum << endl;
        break;
      }
    }
  }
}
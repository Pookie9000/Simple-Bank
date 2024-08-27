#include "SavingsAccount.h"

class BankAccount {

public:
//Default constructor. was unsure if neccessary but included anyways as good practice.
  BankAccount(string firstLetterOfFirstAndLastName = "N/A", string ssn = "000-00-0000") {
    this->firstLetterOfFirstAndLastName = firstLetterOfFirstAndLastName;
    this->ssn = ssn;
  }

//generates a random bank account number
void bankAccountNumberGenerator() {
  int randomNumber = rand() % 10000;
  bankAccountNumberHolder = "BNK" + to_string(randomNumber);
}

//creates a bank account
void createBankAccount();

//displays aggregated amount of balances of all sub accounts within a bank. takes ssn and savings/checking account objects respectfully.
void briefBalanceInfo(SavingsAccount savAccountObj, CheckingAccount chckAccountObj) {
  double total = 0;
  total = savAccountObj.aggregatedBalOfAll() + chckAccountObj.aggregatedBalOfAll();
  cout << "Aggregated Balance of all bank sub-accounts: ";
  cout << total << endl;
  cout << endl;
}

//displays aggregated amount of sub-accounts within bank account. takes ssn and savings/checking account objects respectfully.
void briefBankInfo(string ssn, SavingsAccount savAccountObj, CheckingAccount chckAccountObj) {
  cout << "Aggregated Balance of the bank account : ";
  bankAccountNumbers.at(ssn);
  cout << " is ";
  savAccountObj.briefSavingsAccountInfo(ssn);
  cout << endl;
  cout << endl;
}

//displays every bank account created within the bank
void allBankAccounts();

//tracks the number of bank accounts creted within the bank
void numBankAccounts() {
  cout << "Number of Bank Accounts: " << bankAccounts.size() << endl;
  cout << endl;
}

//displays aggregated balance of all sub accounts within a bank account. takes ssn and savings/checking account objects respectfully.
void aggregatedBalance(string ssn, SavingsAccount savAccountObj, CheckingAccount chkAccountObj) {
  double aggregatedBalance = 0;
  aggregatedBalance = aggregatedBalance + savAccountObj.briefSavingsAccountInfo(ssn) + chkAccountObj.briefCheckingAccountInfo(ssn);
  cout << aggregatedBalance;
}

//tracks the total number of sub-accounts created within a bank account. takes ssn and savings/checking account objects respectfully.
void trackNumberOfSubAccounts(string ssn, SavingsAccount savAccountObj, CheckingAccount chkAccountObj) {
  int numAccounts = 0;
  numAccounts = numAccounts + savAccountObj.trackNumSavingsAccounts(ssn) + chkAccountObj.trackNumCheckingAccounts(ssn);
  cout << numAccounts;
}

//allows deletion of bank account. purges all associated sub-accounts.
void clearBankAccount(string name, string ssn, SavingsAccount savAccountObj, CheckingAccount chkAccountObj);

//Checks if Bank account exists. Used for potential errors. takes ssn as input. 
int accountExists(string ssn) {
  for (auto& bankAccount : bankAccounts) {
    if (bankAccount.second == ssn) {
      return 0;
    }
  }
  return -1;
}

//main hub for bank account. shows all actions a user can take for their bank account. takes ssn and savings, checking account objects as input.
void bankAccountMenu(string ssn, SavingsAccount savAccountObj, CheckingAccount chckAccountObj);


private:
map<string, string> bankAccounts; //Stores (first letters of first and last name, ssn)
map<string, string> bankAccountNumbers; //Stores (ssn, BNK1000)
string bankAccountNumberHolder; //temporaily holds bank account number e.g. BNK1000

//makes the constructor work. Gets overwritten 
string firstLetterOfFirstAndLastName;
string ssn;
};


void BankAccount::createBankAccount() {
  string firstLetterOfFirstNameAndLastName;
  string ssn;
  cout << "Enter the first letter of first/last name of the account holder: ";
  cin >> firstLetterOfFirstNameAndLastName;
  cout << "Enter the SSN of the account holder: ";
  cin >> ssn;
  bankAccountNumberGenerator();
  cout << "A new Bank Account " << bankAccountNumberHolder << " was successfully created." << endl;
  cout << endl;
  bankAccounts.emplace(firstLetterOfFirstNameAndLastName, ssn);
  bankAccountNumbers.emplace(ssn, bankAccountNumberHolder); 
}

void BankAccount::allBankAccounts() {
  cout << "Bank Accounts: " << endl;
  for (auto& bankAccount : bankAccounts) {
    cout << "Account Holder: " << bankAccount.first << endl;
    cout << "SSN: " << bankAccount.second << endl;
    cout << "Bank Account Number: " << bankAccountNumbers.at(bankAccount.second) << endl;
    cout << endl;
  }
}

void BankAccount::clearBankAccount(string name, string ssn, SavingsAccount savAccountObj, CheckingAccount chkAccountObj) {
  if (bankAccounts.find(name) == bankAccounts.end()) {
    cout << "Account does not exist." << endl;
    cout << endl;
  } else {
  savAccountObj.purgeSavingsAccount(ssn);
  bankAccountNumbers.erase(ssn);
  bankAccounts.erase(name);
    //add checking account
  cout << "Bank Account, and all associated sub-accounts, was successfully closed." << endl;
  cout << endl;
  }
}


void BankAccount::bankAccountMenu(string ssn, SavingsAccount savAccountObj, CheckingAccount chckAccountObj) {
    char choice = ' ';
  while (choice != 'Z' || choice != 'z') {
    cout << "Eligible services for " << bankAccountNumbers.at(ssn) << endl;
    cout << "  S -- Open Saving Sub-Account" << endl;
    cout << "  C -- Open Checking Sub-Account" << endl;
    cout << "  M -- Modify a Sub-Account" << endl;
    cout << "  E -- Close a Sub-Account" << endl;
    cout << "  B -- Brief Bank Account Info" << endl;
    cout << "  X -- Exit" << endl;
    cout << "Please enter your selection: ";

    cin >> choice;
    cout << endl;

      if (choice == 'S' || choice == 's') {
        string ssn;
        cout << "Enter you SSN: ";
        cin >> ssn;
        savAccountObj.createSavingsAccount(ssn, savAccountObj);
      }
      if (choice == 'C' || choice == 'c') {
        string ssn;
        cout << "Enter you SSN: ";
        cin >> ssn;
        chckAccountObj.createCheckingAccount(ssn, chckAccountObj);
      }
      if (choice == 'M' || choice == 'm') {
        string subAccountNum;
        char choice = ' ';
        cout << "  C - Modify checking account" << endl;
        cout << "  S - Modify saving account" << endl;
        cout << "Enter selection: ";
        cin >> choice;
        if (choice == 'C' || choice == 'c') {
        cout << "Enter the sub-account number to modify: ";
          cin >> subAccountNum;
          chckAccountObj.checkingAccountMenu(subAccountNum);
          } else if (choice == 'S' || choice == 's') {
          cout << "Enter the sub-account number to modify: ";
          cin >> subAccountNum;
          savAccountObj.savingsAccountMenu(subAccountNum);
      }
  }

      if (choice == 'E' || choice == 'e') {
        string subAccountNum;
        char choice = ' ';
        cout << "Which sub-account would you like to close? " << endl;
        cout << "To close savings account, enter 'S'." << endl;
        cout << "To close checking account, enter 'C'." << endl;
        cout << "Enter selection: ";
        cin >> choice;
        if (choice == 'S' || choice == 's') {
          cout << "Enter the sub-account number to be closed: ";
          cin >> subAccountNum;
          savAccountObj.clearSavingsAccount(ssn, subAccountNum);
        } else if (choice == 'C' || choice == 'c') {
          cout << "Enter the sub-account number to be closed: ";
          cin >> subAccountNum;
          chckAccountObj.clearCheckingAccount(ssn, subAccountNum);
        }      
      }
    if (choice == 'B' || choice == 'b') {
      briefBankInfo(ssn, savAccountObj, chckAccountObj);
    }

    if (choice == 'X' || choice == 'x') {
      cout << "End of service for bank account " << bankAccountNumbers.at(ssn) << endl;
      break;
    }
  }
  }
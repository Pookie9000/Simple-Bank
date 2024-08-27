#include "BankAccount.h"

class Bank {

public:
//Default constructor
Bank(string bankName = "N/A", string bankAddress = "N/A", string workingHours = "Mon - Sat 00:00 - 00:00") {
  this->bankName = bankName;
  this->bankAddress = bankAddress;
  this->workingHours = workingHours;
}

//creates a bank
void createBank() {
  cout << "Enter the name of the bank: ";
  getline(cin, bankName);
  cout << "Enter the address of the bank: ";
  getline(cin, bankAddress);
  cout << "Enter the working hours: ";
  getline(cin, workingHours);
  cout << endl;
}

//basic getter function that outputs bank name, address, and working hours.
void getBankName() {
  cout << "Bank: " << bankName << endl;
  cout << "bank address: " << bankAddress << endl;
  cout << "bank hours: " << workingHours << endl;
}

//main hub for bank. shows all actions user can take within the bank. takes bank, savings, and checing account objects respectfully.
void bankMenu(BankAccount bankAccountObj, SavingsAccount savAccountObj, CheckingAccount chckAccountObj);

private:
string bankName;
string bankAddress;
string workingHours;
};



void Bank::bankMenu(BankAccount bankAccountObj, SavingsAccount savAccountObj, CheckingAccount chckAccountObj) {
  char choice = ' ';
while (choice != 'X' || choice != 'x') {
  cout << "Eligible services for " << bankName << endl;
  cout << "  A -- Number of Bank-Accounts" << endl;
  cout << "  S -- Number of Saving-Accounts" << endl;
  cout << "  H -- Number of Checking-Accounts" << endl;
  cout << "  O -- Open Bank-Account" << endl;
  cout << "  C -- Close Bank-Account" << endl;
  cout << "  M -- Modify Bank-Account" << endl;
  cout << "  D -- Detailed Bank-Accounts" << endl;
  cout << "  B -- Brief Bank-Accounts Info" << endl;
  cout << "  X -- Exit" << endl;
  cout << "Please enter your selection: ";

    cin >> choice;
    if (choice == 'A' || choice == 'a') {
      bankAccountObj.numBankAccounts();
    }
    
    if (choice == 'S' || choice == 's') {
      savAccountObj.totalNumSavingsAccounts();
    }
    if (choice == 'H' || choice == 'h') {
      chckAccountObj.numCheckingAccounts();
    }

    if (choice == 'O' || choice == 'o') {
      bankAccountObj.createBankAccount();
    }
    if (choice == 'C' || choice == 'c') {
      string ssn;
      string name;
      cout << "Enter the first letter of first/last name: ";
      cin >> name;
      cout << "Please enter SSN: ";
      cin >> ssn;
      bankAccountObj.clearBankAccount(name, ssn, savAccountObj, chckAccountObj);
    }

    if (choice == 'M' || choice == 'm') {
      string ssn;
      cout << "Enter the SSN of the account holder: ";
      cin >> ssn;
      if (bankAccountObj.accountExists(ssn) == -1) {
        cout << "Account does not exist." << endl;
        cout << endl;
      } else {
      cout << endl;
      bankAccountObj.bankAccountMenu(ssn, savAccountObj, chckAccountObj);
      }
    }

    if (choice == 'D' || choice == 'd') {
      bankAccountObj.allBankAccounts();
    }

    if (choice == 'B' || choice == 'b') {
      bankAccountObj.briefBalanceInfo(savAccountObj, chckAccountObj);
    }

    if (choice == 'X' || choice == 'x') {
      break;
    }
  }
}
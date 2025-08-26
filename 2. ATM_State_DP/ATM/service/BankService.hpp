#include "../common_include_files.hpp"
#include "../model/Card.h"
#include "../model/BankAccount.h"

class BankService {
    public:
        static bool authenticatePin(Card* card, int enteredPin) {
            cout<<"Authenticating";
            if(card->pin == enteredPin) return true;
            else return false;
        }

        static double getBalance(BankAccount* account) {
            cout << "[BankService] Fetching balance for account: " << account->accountNumber << "..." << endl;
            cout << "[BankService] Balance is: $" << account->balance << endl;
            return account->balance;
        }

        static bool processWithdrawal(BankAccount* account, double amount) {
            cout << "[BankService] Processing withdrawal of $" << amount << " from account: " << account->accountNumber << "..." << endl;
            if (account->balance >= amount) {
                account->balance -= amount;
                cout << "[BankService] Withdrawal successful. New balance: $" << account->balance << endl;
                return true;
            }
            cout << "[BankService] Withdrawal failed. Insufficient funds in your account." << endl;
            return false;
        }
        
        static bool processDeposit(BankAccount* account, double amount) {
            cout << "[BankService] Processing deposit of $" << amount << " to account: " << account->accountNumber << "..." << endl;
            account->balance += amount;
            cout << "[BankService] Deposit successful. New balance: $" << account->balance << endl;
            return true;
        }
};

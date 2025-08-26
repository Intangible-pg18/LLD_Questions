#include "common_include_files.hpp"
#include "ATM.hpp"
#include "model/Card.h"
#include "model/BankAccount.h"
#include "state/StateFactory.hpp" 

using namespace std;

int main() {
    cout << "Application starting... Initializing ATM and user data." << endl;
    ATM* atm = new ATM(5000.0);
    Card* userCard = new Card("1234-5678-9876-5432", "12/25", 1234);
    BankAccount* userAccount = new BankAccount("ACC987654321", 1500.0);
    
    atm->setBankAccount(userAccount);
    cout << "Initialization complete." << endl;

    while (true) {
        cout << "\n========================================" << endl;
        cout << "Welcome! The ATM is in an IDLE state." << endl;
        cout << "1. Insert Card" << endl;
        cout << "9. Shut Down ATM" << endl;
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        if (choice == 9) {
            break; 
        }

        if (choice == 1) {
            try {
                atm->insertCard(userCard);
                cout << "Please enter your 4-digit PIN: ";
                int pin;
                cin >> pin;
                atm->enterPin(pin);
                if (dynamic_cast<EjectingCardState*>(atm->getCurrentState())) {
                    cout << "Transaction aborted due to incorrect PIN." << endl;
                    atm->ejectCard();
                    continue;
                }
                
                cout << "\nPlease select an operation:" << endl;
                cout << "1. Withdraw Cash" << endl;
                cout << "2. Deposit Cash" << endl;
                cout << "3. Check Balance" << endl;
                cout << "4. Cancel" << endl;
                cout << "Enter your choice: ";
                
                int opChoice;
                cin >> opChoice;

                if (opChoice == 4) { 
                    atm->cancel();
                    atm->ejectCard();
                    continue; 
                }
                
                atm->selectOperation(opChoice);

                if (dynamic_cast<AcceptingWithdrawalAmountState*>(atm->getCurrentState()) ||
                    dynamic_cast<AcceptingDepositState*>(atm->getCurrentState())) {
                    
                    double amount;
                    cin >> amount;
                    atm->enterAmount(amount);
                }

                if (dynamic_cast<ProcessingWithdrawalState*>(atm->getCurrentState()) ||
                    dynamic_cast<ProcessingDepositState*>(atm->getCurrentState())) {
                    
                    atm->processTransaction();
                }

                if (dynamic_cast<DispensingCashState*>(atm->getCurrentState())) {
                    atm->dispenseCash();
                }
    
                cout << "Transaction finished." << endl;
                atm->ejectCard();

            } catch (const runtime_error& e) {
                cout << "ERROR: " << e.what() << endl;
                cout << "An unexpected error occurred. Ejecting card." << endl;
                if (atm->getCurrentCard() != nullptr) {
                   atm->setCurrentState(StateFactory::createState(EJECTING_CARD, atm));
                   atm->ejectCard();
                }
            }
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    cout << "\nATM shutting down. Thank you!" << endl;

    return 0;
}
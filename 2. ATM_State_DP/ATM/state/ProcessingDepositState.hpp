#pragma once
#include "ATMState.hpp"
#include "StateFactory.hpp"
#include "../ATM.hpp"
#include "../service/BankService.hpp"

class ProcessingDepositState : public ATMState {
public:
    void processTransaction(ATM* atm) override {
        cout << "STATE: ProcessingDeposit -> EjectingCard" << endl;
        double amount = atm->getTransactionAmount();
        cout << "Counting deposited cash... Amount: $" << amount << endl;
        
        if (BankService::processDeposit(atm->getBankAccount(), amount)) {
            atm->updateCashInMachine(amount); // Increase cash
            cout << "Deposit confirmed." << endl;
        } else {
            cout << "Bank error during deposit. Returning cash." << endl;
        }
        atm->setCurrentState(StateFactory::createState(EJECTING_CARD));
    }
};
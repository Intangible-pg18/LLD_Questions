#pragma once
#include "ATMState.hpp"
#include "StateFactory.hpp"
#include "../ATM.hpp"
#include "../service/BankService.hpp"

class ProcessingWithdrawalState : public ATMState {
public:
    void processTransaction(ATM* atm) override {
        double amount = atm->getTransactionAmount();
        cout << "STATE: ProcessingWithdrawal..." << endl;

        if (amount > atm->getCashInMachine()) {
            cout << "ATM has insufficient cash. Please try a smaller amount or another machine." << endl;
            atm->setCurrentState(StateFactory::createState(EJECTING_CARD));
            return;
        }

        if (BankService::processWithdrawal(atm->getBankAccount(), amount)) {
            cout << "Bank approved withdrawal." << endl;
            atm->setCurrentState(StateFactory::createState(DISPENSING_CASH));
        } else {
            cout << "Bank denied withdrawal (e.g., insufficient funds)." << endl;
            atm->setCurrentState(StateFactory::createState(EJECTING_CARD));
        }
    }
};
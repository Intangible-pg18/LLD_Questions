#pragma once
#include "ATMState.hpp"
#include "StateFactory.hpp"
#include "../ATM.hpp"

class AcceptingDepositState : public ATMState {
public:
    AcceptingDepositState(ATM* atm) : ATMState(atm) {
        cout << "Please enter the amount to deposit: ";
    }

    void enterAmount(double amount) override {
        cout << "STATE: AcceptingDeposit -> ProcessingDeposit" << endl;
        this->atm->setTransactionAmount(amount);
        this->atm->setCurrentState(StateFactory::createState(PROCESSING_DEPOSIT, this->atm));
    }

    void cancel() override {
        cout << "Deposit cancelled." << endl;
        this->atm->setCurrentState(StateFactory::createState(EJECTING_CARD, this->atm));
    }
};
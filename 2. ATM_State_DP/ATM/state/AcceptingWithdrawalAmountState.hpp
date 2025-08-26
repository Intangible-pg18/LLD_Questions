#pragma once
#include "ATMState.hpp"
#include "StateFactory.hpp"
#include "../ATM.hpp"

class AcceptingWithdrawalAmountState : public ATMState {
public:
    AcceptingWithdrawalAmountState(ATM* atm) : ATMState(atm) {
        cout << "Please enter the amount to withdraw: ";
    }

    void enterAmount(double amount) override {
        cout << "STATE: AcceptingWithdrawalAmount -> ProcessingWithdrawal" << endl;
        this->atm->setTransactionAmount(amount);
        this->atm->setCurrentState(StateFactory::createState(PROCESSING_WITHDRAWAL, this->atm));
    }

    void cancel() override {
        cout << "Withdrawal cancelled." << endl;
        this->atm->setCurrentState(StateFactory::createState(EJECTING_CARD, this->atm));
    }
};
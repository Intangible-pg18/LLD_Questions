#pragma once
#include "ATMState.hpp"
#include "StateFactory.hpp"
#include "../ATM.hpp"

class PinAuthenticatedState : public ATMState {
public:
    PinAuthenticatedState(ATM* atm) : ATMState(atm) {}

    void selectOperation(int opType) override {
        switch (opType) {
            case 1: // WITHDRAW
                cout << "STATE: PinAuthenticated -> AcceptingWithdrawalAmount" << endl;
                this->atm->setCurrentState(StateFactory::createState(ACCEPTING_WITHDRAWAL_AMOUNT, this->atm));
                break;
            case 2: // DEPOSIT
                cout << "STATE: PinAuthenticated -> AcceptingDeposit" << endl;
                this->atm->setCurrentState(StateFactory::createState(ACCEPTING_DEPOSIT, this->atm));
                break;
            case 3: // CHECK BALANCE
                cout << "Checking balance..." << endl;
                BankService::getBalance(this->atm->getBankAccount());
                this->atm->setCurrentState(StateFactory::createState(EJECTING_CARD, this->atm));
                break;
            default:
                cout << "Invalid selection. Cancelling." << endl;
                this->atm->setCurrentState(StateFactory::createState(EJECTING_CARD, this->atm));
                break;
        }
    }

    void cancel() override {
        cout << "Transaction cancelled." << endl;
        this->atm->setCurrentState(StateFactory::createState(EJECTING_CARD, this->atm));
    }
};
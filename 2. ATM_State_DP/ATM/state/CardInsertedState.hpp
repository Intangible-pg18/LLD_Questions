#pragma once
#include "ATMState.hpp"
#include "StateFactory.hpp"
#include "../ATM.h"
#include "../service/BankService.hpp"

class CardInsertedState : public ATMState {
public:
    CardInsertedState(ATM* atm) : ATMState(atm) {}

    void enterPin(int pin) override {
        if (BankService::authenticatePin(this->atm->getCurrentCard(), pin)) {
            cout << "STATE: CardInserted -> PinAuthenticated" << endl;
            cout << "PIN authentication successful." << endl;
            this->atm->setCurrentState(StateFactory::createState(PIN_AUTHENTICATED, this->atm));
        } else {
            cout << "Incorrect PIN. Ejecting card." << endl;
            this->atm->setCurrentState(StateFactory::createState(EJECTING_CARD, this->atm));
        }
    }

    void cancel() override {
        cout << "Transaction cancelled." << endl;
        this->atm->setCurrentState(StateFactory::createState(EJECTING_CARD, this->atm));
    }
};
#pragma once
#include "ATMState.hpp"
#include "StateFactory.hpp"
#include "../ATM.hpp"

class DispensingCashState : public ATMState {
public:
    void dispenseCash(ATM* atm) override {
        cout << "STATE: DispensingCash -> EjectingCard" << endl;
        double amount = atm->getTransactionAmount();
        atm->updateCashInMachine(-amount); // Decrease cash
        cout << "Please take your cash: $" << amount << endl;
        
        // Check if ATM is now out of cash
        if (atm->getCashInMachine() <= 0) {
            cout << "ALERT: ATM is now out of cash." << endl;
            // The final eject state will move it to OutOfService
        }
        
        atm->setCurrentState(StateFactory::createState(EJECTING_CARD));
    }
};
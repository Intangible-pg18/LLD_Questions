#pragma once
#include "ATMState.hpp"
#include "StateFactory.hpp"
#include "../ATM.hpp"

class EjectingCardState : public ATMState {
public:
    void ejectCard(ATM* atm) override {
        cout << "Please take your card." << endl;
        atm->setCurrentCard(nullptr);
        
        // After transaction, if cash is depleted, move to OutOfService
        if (atm->getCashInMachine() <= 0) {
            cout << "STATE: EjectingCard -> OutOfService" << endl;
            atm->setCurrentState(StateFactory::createState(OUT_OF_SERVICE));
        } else {
            cout << "STATE: EjectingCard -> Idle" << endl;
            atm->setCurrentState(StateFactory::createState(IDLE));
        }
    }
};
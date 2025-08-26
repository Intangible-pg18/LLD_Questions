#pragma once
#include "ATMState.hpp"
#include "StateFactory.hpp"
#include "../ATM.hpp"

class IdleState : public ATMState {
public:
    IdleState(ATM* atm) : ATMState(atm) {}
    void insertCard(Card* card) override {
        cout << "STATE: Idle -> CardInserted" << endl;
        cout << "Card has been inserted. Please enter your PIN." << endl;
        atm->setCurrentCard(card);
        atm->setCurrentState(StateFactory::createState(CARD_INSERTED));
    }
};
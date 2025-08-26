#pragma once
#include "ATMState.hpp"

class OutOfServiceState : public ATMState {
private:
    void displayOOSMessage() {
        cout << "This ATM is currently out of service. Please try again later." << endl;
    }
public:
    void insertCard(Card* card) override { displayOOSMessage(); }
    void enterPin(int pin) override { displayOOSMessage(); }
    void selectOperation(int opType, double amount) override { displayOOSMessage(); }
    void processTransaction() override { displayOOSMessage(); }
    void dispenseCash() override { displayOOSMessage(); }
    void ejectCard() override { displayOOSMessage(); }
    void cancel() override { displayOOSMessage(); }
};
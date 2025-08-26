#include "../common_include_files.hpp"
#include "../model/Card.h"
#include "../ATM.hpp"

class ATMState {
    public:
        ATM* atm;

        virtual void insertCard(Card* card) {
            throw runtime_error("Invalid operation in current state.");
        }
        virtual void enterPin(int pin) {
            throw runtime_error("Invalid operation in current state.");
        }
        virtual void enterAmount(double amount) { 
            throw runtime_error("Invalid operation."); 
        }
        virtual void selectOperation(int operationType, double amount) {
            throw runtime_error("Invalid operation in current state.");
        }
        virtual void processTransaction() {
            throw runtime_error("Invalid operation in current state.");
        }
        virtual void dispenseCash() {
            throw runtime_error("Invalid operation in current state.");
        }
        virtual void ejectCard() {
            throw runtime_error("Invalid operation in current state.");
        }
        virtual void cancel() {
            throw runtime_error("Invalid operation in current state.");
        }
};
#include "state/ATMState.hpp"
#include "model/Card.h"
#include "model/BankAccount.h"
#include "common_include_files.hpp"

class ATMState;
class Card;
class BankAccount;

class ATM {
private:
    ATMState* currentState;
    double cashInMachine;
    Card* currentCard;
    BankAccount* bankAccount;
    double currentTransactionAmount;

public:
    ATM(double initialCash);
    void setCurrentState(ATMState* state);
    ATMState* getCurrentState();
    // --- Data Getters and Setters (used by States and Controller) ---
    void updateCashInMachine(double amount);
    double getCashInMachine();
    void setCurrentCard(Card* card);
    Card* getCurrentCard();
    void setBankAccount(BankAccount* account);
    BankAccount* getBankAccount();
    void setTransactionAmount(double amount);
    double getTransactionAmount();
    // --- User Actions (Delegated to the Current State) ---
    void insertCard(Card* card);
    void enterPin(int pin);
    void selectOperation(int opType);
    void enterAmount(double amount);
    void processTransaction();
    void dispenseCash();
    void ejectCard();
    void cancel();
};
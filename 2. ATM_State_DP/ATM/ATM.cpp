#include "common_include_files.hpp"
#include "ATM.hpp"
#include "state/StateFactory.hpp" 


ATM::ATM(double initialCash) {
    this->cashInMachine = initialCash;
    this->currentCard = nullptr;
    this->bankAccount = nullptr;
    this->currentTransactionAmount = 0.0;

    if (initialCash <= 0) {
        this->currentState = StateFactory::createState(OUT_OF_SERVICE, this);
        cout << "ATM initialized in Out Of Service state." << endl;
    } else {
        this->currentState = StateFactory::createState(IDLE, this);
        cout << "ATM initialized with $" << initialCash << ". Current State: Idle" << endl;
    }
}


void ATM::setCurrentState(ATMState* state) {
    this->currentState = state;
}

ATMState* ATM::getCurrentState() {
    return this->currentState;
}

void ATM::updateCashInMachine(double amount) {
    this->cashInMachine += amount; 
}

double ATM::getCashInMachine() {
    return this->cashInMachine;
}

void ATM::setCurrentCard(Card* card) {
    this->currentCard = card;
}

Card* ATM::getCurrentCard() {
    return this->currentCard;
}

void ATM::setBankAccount(BankAccount* account) {
    this->bankAccount = account;
}

BankAccount* ATM::getBankAccount() {
    return this->bankAccount;
}

void ATM::setTransactionAmount(double amount) {
    this->currentTransactionAmount = amount;
}

double ATM::getTransactionAmount() {
    return this->currentTransactionAmount;
}

void ATM::insertCard(Card* card) {
    this->currentState->insertCard(card);
}

void ATM::enterPin(int pin) {
    this->currentState->enterPin(pin);
}

void ATM::selectOperation(int opType) {
    this->currentState->selectOperation(opType);
}

void ATM::enterAmount(double amount) {
    this->currentState->enterAmount(amount);
}

void ATM::processTransaction() {
    this->currentState->processTransaction();
}

void ATM::dispenseCash() {
    this->currentState->dispenseCash();
}

void ATM::ejectCard() {
    this->currentState->ejectCard();
}

void ATM::cancel() {
    this->currentState->cancel();
}
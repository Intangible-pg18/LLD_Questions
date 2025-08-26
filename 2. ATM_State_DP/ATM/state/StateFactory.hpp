#include "../common_include_files.hpp"
#include "IdleState.hpp"
#include "ATMState.hpp"
#include "CardInsertedState.hpp"
#include "PinAuthenticatedState.hpp"
#include "AcceptingWithdrawalAmountState.hpp"
#include "ProcessingWithdrawalState.hpp"
#include "DispensingCashState.hpp"
#include "AcceptingDepositState.hpp"
#include "ProcessingDepositState.hpp"
#include "EjectingCardState.hpp"
#include "OutOfServiceState.hpp"


class IdleState;
class CardInsertedState;
class PinAuthenticatedState;
class AcceptingWithdrawalAmountState;
class ProcessingWithdrawalState;
class DispensingCashState;
class AcceptingDepositState;
class ProcessingDepositState;
class EjectingCardState;
class OutOfServiceState;


enum StateType {
    IDLE,
    CARD_INSERTED,
    PIN_AUTHENTICATED,
    ACCEPTING_WITHDRAWAL_AMOUNT,
    PROCESSING_WITHDRAWAL,
    DISPENSING_CASH,
    ACCEPTING_DEPOSIT,
    PROCESSING_DEPOSIT,
    EJECTING_CARD,
    OUT_OF_SERVICE
};

class StateFactory {
public:
    ATMState* StateFactory::createState(StateType type, ATM* atm) {
        switch (type) {
            case IDLE: return new IdleState(atm);
            case CARD_INSERTED: return new CardInsertedState(atm);
            case PIN_AUTHENTICATED: return new PinAuthenticatedState(atm);
            case ACCEPTING_WITHDRAWAL_AMOUNT: return new AcceptingWithdrawalAmountState(atm); 
            case ACCEPTING_DEPOSIT: return new AcceptingDepositState(atm);                   
            case PROCESSING_WITHDRAWAL: return new ProcessingWithdrawalState(atm);
            case DISPENSING_CASH: return new DispensingCashState(atm);
            case PROCESSING_DEPOSIT: return new ProcessingDepositState(atm);
            case EJECTING_CARD: return new EjectingCardState(atm);
            case OUT_OF_SERVICE: return new OutOfServiceState(atm);
            default: return nullptr;
        }
    }
};
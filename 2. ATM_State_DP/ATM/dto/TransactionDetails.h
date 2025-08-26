#pragma once
#include <stdio.h>
#include <string>

using namespace std;

enum TransactionType {
    WITHDRAWAL,
    DEPOSIT,
    BALANCE_INQUIRY
};

class TransactionDetails {
public:
    string transactionId;
    TransactionType type;
    double amount;
    bool status; // true for success, false for failure
};
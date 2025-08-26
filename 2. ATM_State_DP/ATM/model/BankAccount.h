#pragma once
#include <stdio.h>
#include <string>

using namespace std;

class BankAccount {
public:
    string accountNumber;
    double balance;

    BankAccount(string accNum, double bal) {
        this->accountNumber = accNum;
        this->balance = bal;
    }
};
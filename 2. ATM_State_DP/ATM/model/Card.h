#pragma once
#include <stdio.h>
#include <string>

using namespace std;

class Card {
public:
    string cardNumber;
    string expiryDate;
    int pin;

    Card(string num, string expiry, int p) {
        this->cardNumber = num;
        this->expiryDate = expiry;
        this->pin = p;
    }
};
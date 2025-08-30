#pragma once
#include "IHandler.h"
#include <string>
using namespace std;
class AbstractHandler : public IHandler {
public:
    IHandler* next;
    string name;
    AbstractHandler(const string& n = "") {
        next = nullptr;
        name = n;
    }
    void setNext(IHandler* n) override {
        next = n;
    }
    void handle(Request* req, Response* res) override {
        if (next) next->handle(req, res);
    }
};

//controller layer
//const in c++
//pass by pointer etc in c++
//security token flow
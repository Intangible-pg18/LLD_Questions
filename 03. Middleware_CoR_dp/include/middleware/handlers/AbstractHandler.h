#pragma once
#include "middleware/core/IHandler.h"
#include <string>
using namespace std;
class AbstractHandler : public IHandler {
public:
    unique_ptr<IHandler> next;
    string name;
    AbstractHandler(string n = "") {
        next = nullptr;
        name = n;
    }
    void setNext(unique_ptr<IHandler> n) override {
        next = move(n);
    }
    void handle(Request* req, Response* res) override {
        if (next) next->handle(req, res);
    }
};
#pragma once
#include "AbstractHandler.h"
#include <iostream>
using namespace std;
class SimpleHandler : public AbstractHandler {
public:
    SimpleHandler(const string& n):AbstractHandler(n){}
    void handle(Request* req, Response* res) override;
};
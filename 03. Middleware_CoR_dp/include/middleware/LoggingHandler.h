#pragma once
#include "AbstractHandler.h"
#include <iostream>
using namespace std;
class LoggingHandler : public AbstractHandler {
public:
    LoggingHandler():AbstractHandler("Logging"){}
    void handle(Request* req, Response* res) override;
};
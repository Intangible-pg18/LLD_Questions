#pragma once
#include "middleware/handlers/AbstractHandler.h"
using namespace std;
class AuthHandler : public AbstractHandler {
public:
    AuthHandler():AbstractHandler("Auth"){}
    void handle(Request* req, Response* res) override;
};
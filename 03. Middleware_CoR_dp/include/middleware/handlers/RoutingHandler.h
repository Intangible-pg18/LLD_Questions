#pragma once
#include "middleware/handlers/AbstractHandler.h"
using namespace std;
class RoutingHandler : public AbstractHandler {
public:
    RoutingHandler():AbstractHandler("Routing"){}
    void handle(Request* req, Response* res) override;
};
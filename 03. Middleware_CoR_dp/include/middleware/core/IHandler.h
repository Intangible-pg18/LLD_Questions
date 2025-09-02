#pragma once
#include <memory>
#include "middleware/entities/Request.h"
#include "middleware/entities/Response.h"
using namespace std;
class IHandler {
public:
    virtual void setNext(unique_ptr<IHandler> next) = 0;
    virtual void handle(Request* req, Response* res) = 0;
};
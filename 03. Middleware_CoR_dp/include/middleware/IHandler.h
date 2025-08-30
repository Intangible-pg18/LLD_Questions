#pragma once
#include "Request.h"
#include "Response.h"
using namespace std;
class IHandler {
public:
    virtual void setNext(IHandler* next) = 0;
    virtual void handle(Request* req, Response* res) = 0;
};
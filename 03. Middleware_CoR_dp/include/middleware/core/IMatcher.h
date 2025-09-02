#pragma once
#include "middleware/entities/Request.h"
using namespace std;
class IMatcher {
public:
    virtual bool matches(Request* req) = 0;
};
#pragma once
#include "middleware/core/IHandler.h"
using namespace std;
class IChainFactory {
public:
    virtual unique_ptr<IHandler> create() = 0;
};
#pragma once
#include "middleware/core/IChainFactory.h"
using namespace std;
class AdminChainFactory : public IChainFactory {
public:
     unique_ptr<IHandler> create() override;
};
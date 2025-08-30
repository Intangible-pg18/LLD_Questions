#pragma once
#include "AbstractHandler.h"
using namespace std;
class CompressionHandler : public AbstractHandler {
public:
    CompressionHandler():AbstractHandler("Compression"){}
    void handle(Request* req, Response* res) override;
};
#pragma once
#include "IHandler.h"
#include <unordered_map>
#include <string>
using namespace std;
class MiddlewareManager {
public:
    unordered_map<string, IHandler*> chains;
    void addChain(const string& name, IHandler* head);
    IHandler* getChain(const string& name);
    void append(const string& chainName, IHandler* handler);
    void prepend(const string& chainName, IHandler* handler);
    void insertAfter(const string& chainName, const string& existingHandlerName, IHandler* handler);
    void removeHandler(const string& chainName, const string& handlerName);
};
#pragma once
#include "middleware/core/Ihandler.h"
#include <unordered_map>
#include <string>
using namespace std;
class MiddlewareManager {
public:
    unordered_map<string, unique_ptr<IHandler>> chains;
    void addChain(const string& name, unique_ptr<IHandler> head);
    IHandler* getChain(const string& name);
    void append(const string& chainName, unique_ptr<IHandler> handler);
    void prepend(const string& chainName, unique_ptr<IHandler> handler);
    void insertAfter(const string& chainName, const string& existingHandlerName, unique_ptr<IHandler> handler);
    void removeHandler(const string& chainName, const string& handlerName);
};
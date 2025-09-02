#pragma once

#include <memory>
#include <string>
#include <vector>

#include "middleware/core/IMatcher.h"
#include "middleware/core/IChainFactory.h"
#include "middleware/core/IHandler.h"         // optional, if you support direct factory objects
#include "middleware/registry/ChainFactoryRegistry.h" // optional, for factory-by-name
#include <middleware/factories/FactoryType.h>

class MiddlewareRouter {
public:
    struct Rule {
        string name;
        unique_ptr<IMatcher> matcher;
        unique_ptr<IChainFactory> factory; // optional direct factory
        FactoryType factoryName;                // optional registry lookup name
        unique_ptr<IHandler> chainHead;    // created lazily
    };

    void addRule(string name, unique_ptr<IMatcher> matcher, unique_ptr<IChainFactory> factory);
    void addRule(string name, unique_ptr<IMatcher> matcher, FactoryType factoryName);

    Rule* findRule(const string& name);

    // find chain for a request (creates chain lazily if necessary)
    IHandler* getChainFor(Request* req);

    // route request using resolved chain (you must adapt Request/Response types)
    void route(Request* req, Response* res);

    // convenience operations to modify a rule's chain (delegates to manager-like logic)
    void insertAfter(const string& ruleName, const string& existingHandlerName, unique_ptr<IHandler> handler);
    void removeHandler(const string& ruleName, const string& handlerName);

private:
    vector<Rule> rules_;
};

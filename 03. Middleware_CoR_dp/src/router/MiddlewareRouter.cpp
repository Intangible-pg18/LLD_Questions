#include "middleware/router/MiddlewareRouter.h"
#include "middleware/handlers/AbstractHandler.h"
#include "middleware/registry/ChainFactoryRegistry.h"
#include <stdexcept>
#include <string>
#include <memory>

using namespace std;

void MiddlewareRouter::addRule(string name, unique_ptr<IMatcher> matcher, unique_ptr<IChainFactory> factory) {
    Rule r;
    r.name = move(name);
    r.matcher = move(matcher);
    r.factory = move(factory);
    rules_.push_back(move(r));
}

void MiddlewareRouter::addRule(string name, unique_ptr<IMatcher> matcher, const string& factoryName) {
    Rule r;
    r.name = move(name);
    r.matcher = move(matcher);
    r.factoryName = factoryName;
    rules_.push_back(move(r));
}

MiddlewareRouter::Rule* MiddlewareRouter::findRule(const string& name) {
    for (auto &r : rules_) if (r.name == name) return &r;
    return nullptr;
}

IHandler* MiddlewareRouter::getChainFor(Request* req) {
    for (auto &r : rules_) {
        if (!r.matcher) continue;
        if (r.matcher->matches(req)) {
            if (!r.chainHead) {
                if (r.factory) {
                    r.chainHead = r.factory->create();
                } else if (!r.factoryName.empty()) {
                    r.chainHead = ChainFactoryRegistry::instance().createChain(r.factoryName);
                }
            }
            return r.chainHead.get();
        }
    }
    return nullptr;
}

void MiddlewareRouter::route(Request* req, Response* res) {
    IHandler* chain = getChainFor(req);
    if (chain) {
        chain->handle(req, res); // adapt to your handle signature
    } else {
        res->status = 404;
        res->body = "Not Found";
    }
}

void MiddlewareRouter::insertAfter(const string& ruleName, const string& existingHandlerName, unique_ptr<IHandler> handler) {
    Rule* r = findRule(ruleName);
    if (!r) return;
    if (!r->chainHead) {
        if (r->factory) r->chainHead = r->factory->create();
        else if (!r->factoryName.empty()) r->chainHead = ChainFactoryRegistry::instance().createChain(r->factoryName);
    }
    if (!r->chainHead) { r->chainHead = move(handler); return; }

    AbstractHandler* cur = dynamic_cast<AbstractHandler*>(r->chainHead.get());
    if (!cur) throw runtime_error("Rule chain head is not an AbstractHandler");

    while (cur) {
        if (cur->name == existingHandlerName) {
            AbstractHandler* newNode = dynamic_cast<AbstractHandler*>(handler.get());
            if (!newNode) throw runtime_error("Inserted handler must be AbstractHandler");
            newNode->setNext(move(cur->next));
            cur->setNext(move(handler));
            return;
        }
        cur = dynamic_cast<AbstractHandler*>(cur->next.get());
    }
}

void MiddlewareRouter::removeHandler(const string& ruleName, const string& handlerName) {
    Rule* r = findRule(ruleName);
    if (!r || !r->chainHead) return;

    AbstractHandler* head = dynamic_cast<AbstractHandler*>(r->chainHead.get());
    if (!head) throw runtime_error("Rule chain head is not an AbstractHandler");

    if (head->name == handlerName) { r->chainHead = move(head->next); return; }

    AbstractHandler* prev = head;
    while (prev->next) {
        AbstractHandler* cur = dynamic_cast<AbstractHandler*>(prev->next.get());
        if (!cur) throw runtime_error("Non-AbstractHandler found inside chain");
        if (cur->name == handlerName) { prev->setNext(move(cur->next)); return; }
        prev = cur;
    }
}

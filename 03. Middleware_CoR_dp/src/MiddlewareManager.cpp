#include "middleware/MiddlewareManager.h"
#include "middleware/AbstractHandler.h"
using namespace std;
void MiddlewareManager::addChain(const string& name, IHandler* head) {
    chains[name] = head;
}
IHandler* MiddlewareManager::getChain(const string& name) {
    auto it = chains.find(name);
    if (it == chains.end()) return nullptr;
    return it->second;
}
void MiddlewareManager::append(const string& chainName, IHandler* handler) {
    IHandler* head = getChain(chainName);
    if (!head) { chains[chainName] = handler; return; }
    AbstractHandler* cur = static_cast<AbstractHandler*>(head);
    while (cur->next) cur = static_cast<AbstractHandler*>(cur->next);
    cur->setNext(handler);
}
void MiddlewareManager::prepend(const string& chainName, IHandler* handler) {
    IHandler* head = getChain(chainName);
    handler->setNext(head);
    chains[chainName] = handler;
}
void MiddlewareManager::insertAfter(const string& chainName, const string& existingHandlerName, IHandler* handler) {
    IHandler* head = getChain(chainName);
    if (!head) { chains[chainName] = handler; return; }
    AbstractHandler* cur = static_cast<AbstractHandler*>(head);
    while (cur) {
        if (cur->name == existingHandlerName) {
            IHandler* oldNext = cur->next;
            cur->setNext(handler);
            handler->setNext(oldNext);
            return;
        }
        if (!cur->next) {
            cur->setNext(handler);
            return;
        }
        cur = static_cast<AbstractHandler*>(cur->next);
    }
}
void MiddlewareManager::removeHandler(const string& chainName, const string& handlerName) {
    IHandler* head = getChain(chainName);
    if (!head) return;
    AbstractHandler* aHead = static_cast<AbstractHandler*>(head);
    if (aHead->name == handlerName) {
        chains[chainName] = aHead->next;
        return;
    }
    AbstractHandler* prev = aHead;
    AbstractHandler* cur = static_cast<AbstractHandler*>(prev->next);
    while (cur) {
        if (cur->name == handlerName) {
            prev->setNext(cur->next);
            return;
        }
        prev = cur;
        cur = static_cast<AbstractHandler*>(cur->next);
    }
}
